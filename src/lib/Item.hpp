#pragma once
#include <string>
#include <iostream>
#include "Serializable.hpp"

class Item : public Serializable {
    std::string nome;
    std::string descricao;
    int id;
    int quantidade;
public:
    Item();
    Item(std::string nome, std::string descricao, int id, int quantidade);

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    const std::string& getNome() const;
    const std::string& getDescricao() const;
    int getId() const;
    int getQuantidade() const;
    void setQuantidade(int q);
};
