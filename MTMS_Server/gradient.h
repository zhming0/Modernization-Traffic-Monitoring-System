#ifndef GRADIENT_H
#define GRADIENT_H
#include<QVector>
class NeuralNetwork;
//!This class is made for the adaption phase of Neural Network.
/*!

  */
class Gradient
{
public:
    Gradient(NeuralNetwork*);

    /*!
      Set gradient in term of threshold.
      @param i represent layer.
      @param j represent the number of a neuron in ith layer.
      @param value represent the value to be set to threshold.
    */
    void setThreshold(int i, int j, double value);

    /*!
      @return gradient in term of threshold.
      @param i represent layer
      @param j represent the number of a neuron in ith layer
    */
    double getThreshold(int i, int j) const;

    /*!
      Increment gradient in term of threshold.
      @param i represent layer.
      @param j represent the number of a neuron in ith layer.
      @param value represent the value to increment.
    */
    void incrementThreshold(int i, int j, double value);

    /*!
        Set gradient in term of weights
        @param i represent layer
        @param j represent the number of a neuron in ith layer
        @param k represent the number of a dendron in above neuron
    */
    void setWeight(int i, int j, int k, double value);
    /*!
        Get gradient in term of a certern dendron's weight
        @return gradient value in term of a certern dendron's weight.
        @param i represent layer
        @param j represent the number of a neuron in ith layer
        @param k represent the number of a dendron in above neuron
    */
    double getWeight(int i, int j, int k) const;
    /*!
        Increment gradient in term of weights
        @param i represent layer
        @param j represent the number of a neuron in ith layer
        @param k represent the number of a dendron in above neuron
    */
    void incrementWeight(int i, int j, int k, double value);

    /*!
        Get the absolute value of gradient in terms of threshold and weight
    */
    double getGradientAbs() const;
protected:
    /*!
        Initialize this class, fill zeros into vectors.
    */
    void init();
    /*!
        Get the root of the sum of square of one vector
    */
    double getVectorAbs(const QVector<double>& vec) const;
private:
    /*!
        Store the gradient value in term of threshold of some neurons
    */
    QVector<QVector<double> > threshold;
    /*!
        Store the gradient value in term of the weight of some connection between neurons.
    */
    QVector<QVector<QVector<double> > > weights;
    /*!
        Store the pointer to whole neural network.
    */
    NeuralNetwork* network;
};

#endif // GRADIENT_H
