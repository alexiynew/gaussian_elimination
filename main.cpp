#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int equation_count = 0, variable_count = 0;
    std::cin >> equation_count >> variable_count;

    std::vector<std::vector<double>> matrix;
    std::vector<double> answers;

    for (int i = 0; i < equation_count; ++i) {
        std::vector<double> equation;
        for (int j = 0; j < variable_count; ++j) {
            double v = 0;
            std::cin >> v;
            equation.push_back(v);
        }
        double a = 0;
        std::cin >> a;
        answers.push_back(a);
        matrix.push_back(equation);
    }

    for (int cv = 0, ce = 0; cv < variable_count; ++cv, ++ce) {
        std::vector<double> current_equation = matrix[ce];
        for (int i = ce + 1; i < equation_count; ++i) {
            std::vector<double>& equation = matrix[i];
            double k = equation[cv] / current_equation[cv];
            for (int j = 0; j < variable_count; ++j) {
                equation[j] = equation[j] - current_equation[j] * k;
            }
        }
    }

    for (int i = 0; i < equation_count; ++i) {
        std::vector<double> equation = matrix[i];
        for (int j = 0; j < variable_count; ++j) {
            std::cout << equation[j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
