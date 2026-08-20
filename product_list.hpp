#ifndef PRODUCT_LIST_HPP
#define PRODUCT_LIST_HPP

#include "product.hpp"

struct ProductList {
    Product value;
    ProductList *next {nullptr};
};

#endif // PRODUCT_LIST_HPP
