#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include<QVector>
#include"neurallayer.h"
#include<QPair>
class Gradient;
//! Neural Network Class for pattern recognization.
/*!
  This class provide a system of N layers feed-forward neural network.
  This class provide the functions to learn some patterns and the functions to recognize some certern pattern.
*/
class NeuralNetwork
{
public:
    /*!
       This contructor take a vector describe the size of this network. Usually use this constructor when learning.
       @param sizeOfNetwork describe the size of network with first element describing the input layer and last element describing the output layer.
    */
    NeuralNetwork(const QVector<int>& sizeOfNetwork);
    /*!
       This constuctor take a path of XML file to construct network for recognizing.
       @param path is a path of some certern XML file.
      */
    NeuralNetwork(const QString& path);
    ~NeuralNetwork();

    /*!
      Learn to recognize some patterns in terms of inputSet and outputSet
      @param inputSet InputSet is the set of inputs correspond to output set.
      @param outputSet OutputSet is the set of outputs correspond to input set.
      @param maxK This is the maximum loop step for learning.
      @param eps This is the maximum error for adaption phase. The loop will last until error < eps.
      @param lambda This is the step length of each adaption.
      @param micro For prevent dead-lock in loop.
    */
    void learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, int maxK, double eps, double lambda, double micro);
    /*!
      Generate output through nueral network, you could call it recognize.
      @return The result calculated by this network.
      @param input Input is input. :)
    */
    QVector<double> test(const QVector<double>& input);

    /*!
      Get number of layers
      @return number of layers in this network.
    */
    int numberOfLayers() const;
    /*!
      Get a certern layer.
      @return The pointer to that layer.
      @param The index of that layer.
    */
    NeuralLayer* getLayer(int index) const;

    /*!
      Save all the value in this network into XML. Next time you can build network using this xml file.
      @param path The path of the xml file.
    */
    void saveToXML(const QString& path);

    /*!
      A special function for character recognization. List all candidates.
      If your job is not about character recognization, just ignore this function.
      @return The candidates of result.
    */
    QString getNetworkString();
    /*!
      Look at getNetworkString();
      @param s The alphaString
    */
    void setNetworkString(QString s);
protected:
    /*!
      Load a xml file to fill this network.
      There is a bad design here. We user "friend" here.
      @param The path of xml file.
    */
    void readFromXML(const QString& path);
    /*!
      Fill this network with random number.
    */
    void genarateRandomNetwork();

    /*!
      Basicly the same with test();
    */
    QVector<double> activate(const QVector<double>& input);
    //Gradient computeTotalGradient(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet);
    /*!
      Compute the partial gradient of the error in terms of thresholds and weights in this network.
      @return The Gradient of the error in terms of thresholds and weights in this network.
      @param requiredOutput Given output, used to calculate error.
    */
    Gradient computePartialGradient(const QVector<double>& requiredOutput);
    /*!
      @return Random number between -1 and 1.
    */
    double random();

    /*!
      A gain function. Just ignore it.
    */
    double gainFunction(double value) const;
private:
    /*!
      Bad design is here.
      This function is a friend of NeuralNetworkXmlHandler
    */
    friend class NeuralNetworkXmlHandler;

    /*!
      The pool of Neural Layer.
    */
    QVector<NeuralLayer*> layers;
    /*!
      AlphaString, you can ignore it.
    */
    QString _networkString;
};

#endif // NEURALNETWORK_H
