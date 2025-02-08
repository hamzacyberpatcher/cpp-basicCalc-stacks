#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

void remSpaces(string& str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            str.erase(str.begin() + i);
            i--;
        }
    }
}

string convert(const string& str)
{
    string res = "";

    stack<char> s;

    unordered_map<char, int> prec{{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'~', 3}};

    for(int i = 0; i < str.length(); i++)
    {
        char token = str[i];

        if (token == '-')
        {
            if (i == 0 || str[i - 1] == '(' || prec.find(str[i - 1]) != prec.end())
                token = '~';
        }

        if (token == '(')
        {
            s.push(token);
        }

        if (token == ')')
        {
            while(s.top() != '(')
            {
                char ch = s.top();
                s.pop();
                res += ch;
            }

            s.pop();
        }

        if (prec.find(token) != prec.end())
        {
            if (token == '~')
            {
                while(!s.empty() && s.top() != '(' && prec[s.top()] > prec[token])
                {
                    char ch = s.top();
                    s.pop();
                    res += ch;
                }

                s.push(token);
            }
            else
            {
                while(!s.empty() && s.top() != '(' && prec[s.top()] >= prec[token])
                {
                    char ch = s.top();
                    s.pop();
                    res += ch;
                }

                s.push(token);
            }
        }
        
        if (token >= '0' && token <= '9')
        {
            res += token;
        }
    }

    
    while(!s.empty())
    {
        char ch = s.top();
        res += ch;
        s.pop();
    }


    return res;

}

int main()
{
    string str = "- 1 + 2";

    string res = "";

    remSpaces(str);

    res = convert(str);

    cout << res << endl;

}
