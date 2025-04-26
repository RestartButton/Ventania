#include <iostream>
#include "Inventario.hpp"

void Inventario::adicionarItem(const Item& item) {
    // Procura se o item já existe no inventário
    for (auto& i : itens) {
        if (i.getId() == item.getId()) {
            i.setQuantidade(i.getQuantidade() + item.getQuantidade());
            return;
        }
    }
    // Se não encontrar, adiciona o item
    itens.push_back(item);
}

void Inventario::exibirInventario() const {
    for (const auto& item : itens) {
        std::cout << "Item: " << item.getNome() << " | Quantidade: " << item.getQuantidade() << std::endl;
    }
}

void Inventario::save(std::ostream& out) const {
    size_t size = itens.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (const Item& item : itens) {
        item.save(out);
    }
}

void Inventario::load(std::istream& in) {
    size_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    itens.resize(size);
    for (Item& item : itens) {
        item.load(in);
    }
}
