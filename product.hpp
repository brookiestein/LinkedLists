#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>

class Product
{
public:
    Product();
    Product(std::string name, int code);
    void setName(std::string name);
    void setCode(int code);
    void add(int quantity);
    void substract(int quantity);
    const std::string &name() const noexcept;
    int code() const noexcept;
    int existence() const noexcept;

private:
    std::string m_name;
    int m_code;
    int m_existence;
};

#endif // PRODUCT_HPP
