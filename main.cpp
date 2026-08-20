#include <boost/convert.hpp>
#include <boost/convert/strtol.hpp>
#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <print>
#include <string>
#include <type_traits>

#include "product.hpp"
#include "product_list.hpp"

std::string input(const std::string &message);

template <typename T>
    requires std::is_arithmetic_v<T>
T getNumber(
    const std::string &message,
    std::function<bool(const T &)> predicate = [](const T &) {
        return true;
    });

void fillProduct(Product &product);

struct boost::cnv::by_default : boost::cnv::strtol {
};

int main()
{
    auto start = std::chrono::steady_clock::now();

    auto numOfProducts = getNumber<int>(
        "Por favor, introduzca la cantidad de productos que desea agregar",
        [](const auto &number) {
            return number > 0;
        });

    auto *head = new ProductList;
    fillProduct(head->value);

    auto *temp = head;
    for (int i {1}; i < numOfProducts; ++i) {
        auto *product = new ProductList;
        fillProduct(product->value);

        temp->next = product;
        temp = temp->next;
    }

    temp = head;
    std::println("|{:^30} | {:^10} | {:^10}|", "NOMBRE", "CÓDIGO",
                 "EXISTENCIA");

    auto s = std::chrono::steady_clock::now();
    while (temp) {
        if (temp->value.existence() < 5) {
            std::println("|{:^30} | {:^10} | {:^10}", temp->value.name(),
                         temp->value.code(), temp->value.existence());
        }

        temp = temp->next;
    }
    auto e = std::chrono::steady_clock::now();
    auto secs = std::chrono::duration_cast<std::chrono::seconds>(e - s);
    std::println("\n<=====TIEMPO DE EJECUCIÓN DE LA FUNCIONALIDAD DE IMPRIMIR "
                 "LOS PRODUCTOS CUYO STOCK SEA MENOR A 5====>");
    std::println("{} segundo{}", secs.count(), secs.count() > 1 ? "s" : "");

    int code = getNumber<int>(
        "Por favor, introduzca el código del producto que desea modificar",
        [](const auto &number) {
            return number > 0;
        });

    temp = head;
    s = std::chrono::steady_clock::now();
    while (temp) {
        if (temp->value.code() == code)
            break;
        temp = temp->next;
    }
    e = std::chrono::steady_clock::now();
    std::println("\n<=====TIEMPO DE EJECUCIÓN DE LA FUNCIONALIDAD DE BUSCAR UN "
                 "PRODUCTO POR CÓDIGO====>");
    std::println("{} segundo{}", secs.count(), secs.count() > 1 ? "s" : "");

    if (temp) {
        int quantity = getNumber<int>(
            std::format("Por favor, introduzca el stock para el producto {}",
                        temp->value.name()),
            [](const auto &number) {
                return number > 0;
            });

        temp->value.add(quantity);

        std::println("¡Éxito! El nuevo stock del producto: {} es: {}.",
                     temp->value.name(), temp->value.existence());
    } else {
        std::println(stderr, "No se encontró ningún producto con código: {}",
                     code);
    }

    auto end = std::chrono::steady_clock::now();
    auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::println("\n<=====TIEMPO TOTAL DE EJECUCIÓN DEL PROGRAMA=====>");
    std::println("{} segundo{}", seconds.count(),
                 seconds.count() > 1 ? "s" : "");
}

std::string input(const std::string &message)
{
    std::string str;

    while (true) {
        std::print("{}: ", message);
        std::getline(std::cin, str);

        if (str.empty()) {
            std::println(stderr, "No introdujiste nada.");
            continue;
        }

        break;
    }

    return str;
}

template <typename T>
    requires std::is_arithmetic_v<T>
T getNumber(const std::string &message,
            std::function<bool(const T &)> predicate)
{
    T number {};

    while (true) {
        std::string str {input(message)};

        try {
            number = boost::convert<T>(str).value();
            if (!predicate(number)) {
                std::println(stderr, "El número introducido no cumple con los "
                                     "criterios establecidos.");
                continue;
            }

            break;
        } catch (...) {
            std::println(
                stderr,
                "Lo que introdujiste no parece ser un número válido: {}", str);
        }
    }

    return number;
}

void fillProduct(Product &product)
{
    auto name = input("Por favor, introduzca el nombre del producto");

    auto code = getNumber<int>(
        std::format("Por favor, introduzca el código del producto {}", name),
        [](const auto &number) {
            return number > 0;
        });

    auto existence = getNumber<int>(
        std::format("Por favor, introduzca la existencia del producto {}",
                    name),
        [](const auto &number) {
            return number >= 0;
        });

    product.setName(name);
    product.setCode(code);
    product.add(existence);
}
