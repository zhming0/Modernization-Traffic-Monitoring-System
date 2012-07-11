#ifndef NEURON_H
#define NEURON_H
#include<QVector>
//! The basic unit of neural network.
/*!
  Neuron is basic unit of neural network which has a threshold and many dendrons.
*/
class Neuron
{
public:
    /*!
      Constructor
      @param numOfDendrons Tell total number of dendrons of this dendron.
      @param threshold Tell the threshold of this neuron.
    */
    Neuron(int numOfDendrons, double threshold);

    /*!
      Get the number of dendrons
      @return The number of dendrons in this Neuron.
    */
    int numberOfDendrons() const;
    /*!
      @return The output of this neuron.
    */
    double getOutput() const;
    /*!
      Set output
      @param value The value to be set as output.
    */
    void setOutput(double value);

    /*!
      Set the threshold of this neuron.
      @param value The value to be set as threshold.
    */
    void setThreshold(double value);
    /*!
      Get the threshold of this neuron.
      @return The threshold of this neuron.
    */
    double getThreshold() const;
    /*!
      Get weight of a certern dendron.
      @param index The index of this dendron.
      @return The weight of a certain dendron.
    */
    double getDendronWeight(int index) const;
    /*!
      Get weight of a certern dendron.
      @param index The index of this dendron.
      @param value The value to be set as dendron.
    */
    void setDendronWeight(int index, double value);
private:
    /*!
      threshold and output.
    */
    double threshold, output;
    /*!
      The pool of dendrons' weight.
    */
    QVector<double> dendronWeight;
};

#endif // NEURON_H
