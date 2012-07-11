#ifndef NEURALLAYER_H
#define NEURALLAYER_H
#include<QVector>
#include"neuron.h"
class NeuralNetwork;
//! Neural layer, which is a class to store neurons.
/*!
  NeuralLayer provide interface to access neurons in side this layer.
*/
class NeuralLayer
{
public:
    /*!
      This NeuralLayer constucter take a pointer of parent network and the number of neurons.
      @param network The pointer to a parent network.
      @param numOfNuerons the number of neurons.
    */
    NeuralLayer(NeuralNetwork* network, int numOfNeurons);
    ~NeuralLayer();
    /*!
      Get number of neurons in this layer.
      PS: Typo in function name :(
      @return The number of neuron in this layer.
    */
    int numberOfNuerons() const;

    /*!
      Get a certern neuron in this layer.
      @return The pointer to that neuron.
      @param The index of that neuron.
    */
    Neuron* getNeuron(int index);
private:
    friend class NeuralNetworkXmlHandler;
    /*!
      The pool of neuron.
    */
    QVector<Neuron*> neurons;
    /*!
      The pointer of parent network.
    */
    NeuralNetwork* network;
};

#endif // NEURALLAYER_H
