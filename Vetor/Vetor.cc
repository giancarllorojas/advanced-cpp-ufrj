#include <iostream>
#include <vector>

using namespace std;

// Cabeçalho das classes
template <unsigned int n, class T> class Vetor;
template <unsigned int n, class T> class MeioDoProdutoVetorial;

// Classe intermediaria necessária para a implementação da sobrecarga do operador **
template <unsigned int n, class T> class MeioDoProdutoVetorial{
  public:
    MeioDoProdutoVetorial(Vetor<n,T> &v){
      this->internal_v = v;
    }

    // Operador de selecao
    T operator [](int index) {
     return this->internal_v[index];
    }

    Vetor<n,T> internal_v;
};

// Sobrecarga do operador << da classe ostream para a classe Vetor
template <unsigned int n, class T> ostream& operator<<(ostream& os, Vetor<n,T> v)
{
  for(int i = 0; i < n; i++){
    os << v[i] << ",";
  }
  return os;
}

template <unsigned int n, class T> Vetor<n,T> operator*(double e, Vetor<n,T> v){
  Vetor<n,T> novo_vetor;
  for(int i=0; i < n; i++){
    novo_vetor.add_element(i,v[i]*e);
  }
  return novo_vetor;
}


// Classe Vetor conforme especificado no Moodle
template <unsigned int n, class T> class Vetor{
  public:
    template <unsigned int n1, class T1> friend ostream& operator<<(ostream& os, Vetor<n1,T1> v);
    template <unsigned int n1, class T1> friend Vetor<n1,T1> operator*(double e, Vetor<n1,T1> v);

    // Método para adicionar um elemento em uma posição especificada
    void add_element(int i, T el){
      this->internal_v[i] = el;
    }

    // Operadores para as multiplicações vetores(Produto escalar e Vetorial)
    T operator*(Vetor<n, T> v){
      double c = 0;
      std::cout << "v x v" << '\n';
      for(int i=0; i < n; i++){
        c += internal_v[i]*v[i];
      }
      return c;
    }

    // Produto vetorial
    MeioDoProdutoVetorial<n,T> operator*(){
      MeioDoProdutoVetorial<n,T> mpv(*this);

      return mpv;
    }
    Vetor operator+(Vetor<n, T> v){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i, internal_v[i] + v[i]);
      }
      return novo_vetor;
    }

    // Operadores de Soma e Subtração
    Vetor operator*(MeioDoProdutoVetorial<n, T> v){
      Vetor<n,T> novo_vetor;
      Vetor<n,T> u = *this;

      // Produto vetorial pro R3
      if(n == 3){
        novo_vetor.add_element(0, u[1]*v[2] - u[2]*v[1]);
        novo_vetor.add_element(1, -1*(u[0]*v[2] - u[2]*v[0]));
        novo_vetor.add_element(2, u[0]*v[1] - u[1]*v[0]);
      }

      return novo_vetor;
    }
    Vetor operator-(Vetor<n, T> v){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i, internal_v[i] - v[i]);
      }
      return novo_vetor;
    }

    // Operadores para multiplicação e divisão por escalar
    Vetor operator*(int e){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i,this->internal_v[i]*e);
      }
      return novo_vetor;
    }
    Vetor operator*(double e){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i,this->internal_v[i]*e);
      }
      return novo_vetor;
    }
    Vetor operator/(int e){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i,this->internal_v[i]/e);
      }
      return novo_vetor;
    }
    Vetor operator/(double e){
      Vetor<n,T> novo_vetor;
      for(int i=0; i < n; i++){
        novo_vetor.add_element(i,this->internal_v[i]/e);
      }
      return novo_vetor;
    }

    // Operador de selecao
    T operator [](int index) {
     return this->internal_v[index];
    }

    // Operadores para a atribuição
    Vetor &operator=(T t){
      this->internal_v[cur_position] = t;
      cur_position++;

      return *this;
    }
    Vetor &operator,(T t){
      this->internal_v[cur_position] = t;
      cur_position++;

      return *this;
    }

  private:
    T internal_v[n];
    int cur_position = 0;
};

int main ()
{
  // Testes
  Vetor<3,double> a;
  Vetor<3,double> b;
  Vetor<3,double> c;
  double d;

  a = 4.5, 6.1, 7.5;
  b = 3.1, 2.8, 9.1;

  c = a**b;

  std::cout << a + b << '\n';
  std::cout << a << '\n';
  std::cout << 2.0*a << '\n';
  std::cout << a*2.0 << '\n';
  std::cout << 3*a << '\n';
  std::cout << a*3 << '\n';

  return 0;
}
