#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED


class Capacidade {
    private:
        int valor;
    public:
        Capacidade(int v);
        void def_valor(int v);
        int get_valor() const;
};

#endif // DOMINIOS_HPP_INCLUDED
