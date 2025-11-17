#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp"
#include <iostream>
#include <string>

/**
 * @class ApresentacaoAutenticacao
 * @brief controladora de apresentação para autenticação
 */
class ApresentacaoAutenticacao : public IApresentacaoAutenticacao {
  private:
      IServicoAutenticacao *servicoAuth;
      IServicoGerente *servicoGerente;
      Email *emailAutenticado;
      
  public:
      ApresentacaoAutenticacao(IServicoAutenticacao *sa, IServicoGerente *sg) : servicoAuth(sa), servicoGerente(sg), emailAutenticado(nullptr) {}
      void executar() override;
      void criarConta();
      bool fazerLogin();
      Email* getEmailAutenticado() { return emailAutenticado; }
};

/**
 * @class ApresentacaoGerente
 * @brief controladora de apresentação para gerentes
 */
class ApresentacaoGerente : public IApresentacaoGerente {
  private:
      IServicoGerente *servico;
      Email *emailLogado;
      
  public:
      ApresentacaoGerente(IServicoGerente *s, Email *email) : servico(s), emailLogado(email) {}
      void menuGerente() override;
      void lerDados();
      void editarDados();
      void excluirConta();
};

/**
 * @class ApresentacaoHotel
 * @brief controladora de apresentação para hotéis
 */
class ApresentacaoHotel : public IApresentacaoHotel {
  private:
      IServicoHotel *servico;
      Email *emailLogado;
      
  public:
      ApresentacaoHotel(IServicoHotel *s, Email *email) : servico(s), emailLogado(email) {}
      void menuHotel() override;
      void criar();
      void ler();
      void editar();
      void excluir();
      void listar();
};

/**
 * @class ApresentacaoQuarto
 * @brief controladora de apresentação para quartos
 */
class ApresentacaoQuarto : public IApresentacaoQuarto {
  private:
      IServicoQuarto *servico;
      Email *emailLogado;
      
  public:
      ApresentacaoQuarto(IServicoQuarto *s, Email *email) : servico(s), emailLogado(email) {}
      void menuQuarto() override;
      void criar();
      void ler();
      void editar();
      void excluir();
      void listar();
};

/**
 * @class ApresentacaoReserva
 * @brief controladora de apresentação para reservas
 */
class ApresentacaoReserva : public IApresentacaoReserva {
  private:
      IServicoReserva *servico;
      IServicoHospede *servicoHospede;
      Email *emailLogado;
      
  public:
      ApresentacaoReserva(IServicoReserva *s, IServicoHospede *sh, Email *email) : servico(s), servicoHospede(sh), emailLogado(email) {}
      void menuReserva() override;
      void criar();
      void ler();
      void editar();
      void excluir();
      void listar();
};

/**
 * @class ApresentacaoHospede
 * @brief controladora de apresentação para hóspedes
 */
class ApresentacaoHospede : public IApresentacaoHospede {
  private:
      IServicoHospede *servico;
      
  public:
      ApresentacaoHospede(IServicoHospede *s) : servico(s) {}
      void menuHospede() override;
      void criar();
      void ler();
      void editar();
      void excluir();
      void listar();
};

/**
 * @class ApresentacaoPrincipal
 * @brief controladora principal do sistema
 */
class ApresentacaoPrincipal {
  private:
      ApresentacaoAutenticacao *apAuth;
      ApresentacaoGerente *apGerente;
      ApresentacaoHotel *apHotel;
      ApresentacaoQuarto *apQuarto;
      ApresentacaoReserva *apReserva;
      ApresentacaoHospede *apHospede;
      
  public:
      ApresentacaoPrincipal(ApresentacaoAutenticacao *aa, ApresentacaoGerente *ag, ApresentacaoHotel *ah, ApresentacaoQuarto *aq,
      ApresentacaoReserva *ar, ApresentacaoHospede *ahosp) : apAuth(aa), apGerente(ag), apHotel(ah), apQuarto(aq), apReserva(ar), apHospede(ahosp) {}
      void executar();
      void menuPrincipal();
};

#endif // APRESENTACAO_HPP_INCLUDED
