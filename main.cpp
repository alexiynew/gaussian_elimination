#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator> // for ostream_iterator

// true - if equation consists of zeros
bool is_zero_equation (const std::vector<double>& eq)
{
    bool res = true;
    for (int i = 0; (i < (int)eq.size() && res); ++i) {
        res &= (eq[i] == 0);
    }
    return res;
}

bool compare_by_first_zeros (const std::vector<double>& eq1, const std::vector<double>& eq2)
{
    int i = 0;
    int j = 0;

    for (; i < (int)eq1.size() && eq1[i] == 0; ++i);
    for (; j < (int)eq2.size() && eq2[j] == 0; ++j);

    return (i < j);
}


void sort_matrix_and_answers (std::vector<std::vector<double> >& matrix, std::vector<double>& answers)
{
    for (int i = 1; i < (int)matrix.size(); ++i) {
        std::vector<double> equation = matrix[i];
        double a = answers[i];
        int j = i - 1;
        while (j >= 0 && compare_by_first_zeros(equation, matrix[j])) {
            matrix[j+1] = matrix[j];
            answers[j+1] = answers[j];
            j--;
        }
        matrix[j+1] = equation;
        answers[j+1] = a;
    }
}

void read_input(std::vector<std::vector<double> >& matrix, std::vector<double>& answers)
{
    int equation_count = 0, variable_count = 0;
    std::cin >> equation_count >> variable_count;

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
}

// delete "zero_equation" from matrix
bool clear_matrix(std::vector<std::vector<double> >& matrix, std::vector<double>& answers)
{
    for (int i = 0; i < (int)matrix.size(); ++i) {
        if (is_zero_equation(matrix[i])) {
            if (answers[i] == 0.0) {
                matrix.erase(matrix.begin() + i);
                answers.erase(answers.begin() + i);
            } else {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    std::vector<std::vector<double> > matrix;
    std::vector<double> answers;

    read_input(matrix, answers);

    int variable_count = matrix[0].size();

    // first pass
    for (int cv = 0; cv < variable_count; ++cv) {

        sort_matrix_and_answers(matrix, answers);

        int cur_eq = cv;

        const std::vector<double>& current_equation = matrix[cur_eq];

        // if number of variables greater than equations, there is infinite number of solutions
        if (cur_eq >= (int)matrix.size()) {
            std::cout << "INF" << std::endl;
            return 0;
        }

        // skip current variable if zero
        if (current_equation[cv] == 0) continue;

        for (int i = cur_eq + 1; i < (int)matrix.size(); ++i) {

            std::vector<double>& equation = matrix[i];
            double k = equation[cv] / current_equation[cv]; // multiply coef

            for (int j = cv; j < (int)equation.size() && j < (int)current_equation.size(); ++j) {
                equation[j] -= current_equation[j] * k;
                if (std::abs(equation[j]) < 0.00000001) equation[j] = 0.0;
            }

            answers[i] -= answers[cur_eq] * k;
            if (std::abs(answers[i]) < 0.00000001) answers[i] = 0.0;
        }

        // if "zero equation" has non zero answer, there is no solutions
        if (!clear_matrix(matrix, answers)) {
            std::cout << "NO" << std::endl;
            return 0;
        }
    }

    // if "zero equation" has non zero answer, there is no solutions
    // double check
    if (!clear_matrix(matrix, answers)) {
        std::cout << "NO" << std::endl;
        return 0;
    }

    // calculate variables
    std::vector<double> variables;

    for (int i = (int)matrix.size() - 1; i >= 0; --i) {
        int cur_var = i;
        double b = 0;
        for (int j = cur_var + 1; j < (int)matrix[i].size(); ++j) {
            b += matrix[i][j];
        }
        double x = (answers[i] - b) / matrix[i][cur_var];
        variables.push_back(x);

        for (int j = i-1; j >= 0; --j) {
            std::vector<double>& equation = matrix[j];
            equation[cur_var] *= x;
        }
    }

    // print variables
    std::cout << "YES" << std::endl;

    std::cout.precision(16);
    std::reverse (variables.begin(), variables.end());
    std::copy(variables.begin(), variables.end(), std::ostream_iterator<double>(std::cout, " "));

    return 0;
}
