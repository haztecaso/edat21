#include <string>
#include <exception>

#define assert_true(e1) _assert_true(#e1, e1)
#define assert_eq(e1, e2) _assert_eq(#e1, #e2, e1, e2)
#define assert_neq(e1, e2) _assert_neq(#e1, #e2, e1, e2)

#define N_TESTS 10000

using namespace std;

class AssertionFailed: public exception
{
    public:
        AssertionFailed(string msg) : m_message(msg) { }
        const char * what () const throw ()
        {
            return m_message.c_str();
        }
    private:
        std::string m_message;
};

// Función para asertar booleanos
void _assert_true(string e1_desc, bool e1);

// Función para asertar igualdades
template <class T> void _assert_eq(string e1_desc, string e2_desc, T e1, T e2);

// Función para asertar desigualdades
template <class T> void _assert_eq(string e1_desc, string e2_desc, T e1, T e2);

/*
 * IMPLEMENTACIONES
 */

void _assert_true(string e1_desc, bool e1)
{
    if(!e1)
        throw AssertionFailed(e1_desc + " is false");
}

template <class T> void _assert_eq(string e1_desc, string e2_desc, T e1, T e2)
{
    string msg = e1_desc + " = " + to_string(e1);
    msg += " is not equal to ";
    msg += e2_desc + " = " + to_string(e2);
    if(e1 != e2)
    {
        throw AssertionFailed(msg);
    }
}

template <class T> void _assert_neq(string e1_desc, string e2_desc, T e1, T e2)
{
    string msg = e1_desc + " = " + to_string(e1);
    msg += " is equal to ";
    msg += e2_desc + " = " + to_string(e2);
    if(e1 == e2)
    {
        throw AssertionFailed(msg);
    }
}
