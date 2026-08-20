#include "product.hpp"

#include <print>
#include <stdexcept>

Product::Product()
    : m_name("")
    , m_code(-1)
    , m_existence(0)
{
}

Product::Product(std::string name, int code)
    : m_name(std::move(name))
    , m_code(code)
    , m_existence(0)
{
    if (m_code < 0)
        throw std::runtime_error("El código debe ser mayor a cero.");
}

void Product::setName(std::string name)
{
    if (!m_name.empty())
        return;

    m_name = std::move(name);
}

void Product::setCode(int code)
{
    if (m_code >= 0)
        return;

    if (code < 0) {
        std::println(stderr, "El código no es válido.");
        return;
    }

    m_code = code;
}

void Product::add(int quantity)
{
    if (quantity <= 0)
        return;

    m_existence += quantity;
}

void Product::substract(int quantity)
{
    if (quantity <= 0)
        return;

    if (m_existence == 0)
        return;

    if ((m_existence - quantity) < 0) {
        std::println(stderr, "No hay suficientes {}.", m_name);
        return;
    }

    m_existence -= quantity;
}

const std::string &Product::name() const noexcept
{
    return m_name;
}

int Product::code() const noexcept
{
    return m_code;
}

int Product::existence() const noexcept
{
    return m_existence;
}
