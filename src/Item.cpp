#include "Item.hpp"

Item::Item() = default;

Item::Item(std::string nome, std::string descricao, int id, int quantidade)
    : nome(std::move(nome)), descricao(std::move(descricao)), id(id), quantidade(quantidade) {}

void Item::save(std::ostream& out) const {
    size_t nomeLen = nome.size();
    size_t descLen = descricao.size();

    out.write(reinterpret_cast<const char*>(&nomeLen), sizeof(nomeLen));
    out.write(nome.c_str(), nomeLen);

    out.write(reinterpret_cast<const char*>(&descLen), sizeof(descLen));
    out.write(descricao.c_str(), descLen);

    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(reinterpret_cast<const char*>(&quantidade), sizeof(quantidade));
}

void Item::load(std::istream& in) {
    size_t nomeLen, descLen;
    in.read(reinterpret_cast<char*>(&nomeLen), sizeof(nomeLen));
    nome.resize(nomeLen);
    in.read(&nome[0], nomeLen);

    in.read(reinterpret_cast<char*>(&descLen), sizeof(descLen));
    descricao.resize(descLen);
    in.read(&descricao[0], descLen);

    in.read(reinterpret_cast<char*>(&id), sizeof(id));
    in.read(reinterpret_cast<char*>(&quantidade), sizeof(quantidade));
}

const std::string& Item::getNome() const { return nome; }
const std::string& Item::getDescricao() const { return descricao; }
int Item::getId() const { return id; }
int Item::getQuantidade() const { return quantidade; }

void Item::setQuantidade(int q) { quantidade = q; }