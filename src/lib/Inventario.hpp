#pragma once
#include <vector>
#include "Item.hpp"

class Inventario : public Serializable {
private:
    std::vector<Item> itens;
public:
    void adicionarItem(const Item& item);
    void exibirInventario() const;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;
};