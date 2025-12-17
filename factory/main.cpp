#include<iostream>
#include<istream>
#include<cmath>
#include<vector>
#include<memory>
#include<string>
#include<fstream>


class CalibFunction
{
    public:
        virtual ~CalibFunction() = default;
        virtual double evaluate(double x) const noexcept = 0;
        virtual void load(std::istream &str) = 0;
};

class Exponential: public CalibFunction
{
    private:
        double a;
        double b;
        double c;
        double x0;
    
    public:
        double evaluate(double x) const noexcept override
        {
            return a  + b*std::exp(c * (x - x0));
        }

        void load(std::istream &str) override
        {
            str >> a >> b >> c >> x0;
            if (!str)
            {
                throw std::runtime_error("Error reading Exponential pars");
            }
        }
};

class Polynomial: public CalibFunction
{
    private: 
        std::vector<double> coeffs;
    
    public:
        double evaluate(double x) const noexcept override
        {
            double result = 0.0;
            double x_pow = 1.0;
            for (const auto &coeff : coeffs)
            {
                result += coeff * x_pow;
                x_pow *= x;
            }
            return result;
        }
        void load(std::istream &str) override
        {
            size_t degree;
            str >> degree;
            if (!str)
            {
                throw std::runtime_error("Error reading Polynomial degree");
            }
            coeffs.resize(degree + 1);
            for (size_t i = 0; i <= degree; ++i)
            {
                str >> coeffs[i];
                if (!str)
                {
                    throw std::runtime_error("Error reading Polynomial coeffs");
                }
            }
        }

};

std::unique_ptr<CalibFunction> factory(std::istream &str) {
    std::string func_type;
    str >> func_type;
    if (!str) {
        throw std::runtime_error("Error reading function type");
    }
    std::unique_ptr<CalibFunction> func;
    if (func_type == "exp") {
        func = std::make_unique<Exponential>();
    } else if (func_type == "poly") {
        func = std::make_unique<Polynomial>();
    } else {
        throw std::runtime_error("Unknown function type: " + func_type);
    }
    func->load(str);
    return func;
}

int main() {
    try {
        std::ifstream file("config.txt");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file");
        }

        std::unique_ptr<CalibFunction> func = factory(file);

        for (double x = 0; x <= 10; x += 0.25) {
            std::cout << "f(" << x << ") = " << func->evaluate(x) << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}