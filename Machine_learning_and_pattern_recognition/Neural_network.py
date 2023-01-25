import pickle
import numpy as np
import tensorflow as tf
from tensorflow.keras.layers import Dense

def unpickle(file):
    with open(file, 'rb') as f:
        dict = pickle.load(f, encoding="latin1")
    return dict

def class_acc(pred, gt):
    correct_labels = 0
    for i in range(0, len(pred)):
        if pred[i] == gt[i]:
            correct_labels += 1

    correct = correct_labels/len(pred)*100
    return correct

def one_hot(list):
    two_dim_list = []

    for number in list:
        row = [0 for i in range(10)]
        row[number] = 1

        two_dim_list.append(row)

    return two_dim_list

def create_network(X, Y, X_test):

    model = tf.keras.models.Sequential()

    model.add(Dense(100, input_dim=3072, activation="sigmoid"))  # input
    model.add(Dense(20, activation = "sigmoid"))
    model.add(Dense(20, activation="sigmoid"))
    model.add(Dense(20, activation="sigmoid"))
    model.add(Dense(20, activation="sigmoid"))
    model.add(Dense(10, activation="sigmoid"))  # output

    opt = tf.keras.optimizers.SGD(learning_rate = 0.7)
    model.compile(optimizer=opt, loss='mse', metrics=['mse'])

    y_tr_2 = np.array(one_hot(Y)) #luokat
    #opetus
    model.fit(np.array(X), np.array(y_tr_2), epochs=100, verbose=1)

    labels = []

    label_probs = model.predict(np.array(X_test))

    for i in label_probs:
        label = np.argmax(i)
        labels.append(label)

    return labels

def main():
    #alustetaan data
    datadict = unpickle("C:\\Users\\Vilma\\Downloads\\cifar-10-python.tar\\"
                        "cifar-10-python\\cifar-10-batches-py\\data_batch_1")
    testdict = unpickle("C:\\Users\\Vilma\\Downloads\\cifar-10-python.tar\\"
                        "cifar-10-python\\cifar-10-batches-py\\test_batch")

    X = datadict["data"]  # kuvat
    Y = datadict["labels"]  # oikeat luokat

    test_X = testdict["data"]  # x muodossa 10000, 3072
    test_Y = testdict["labels"]

    #muutetaan labelit one hot muotoon
    #one_hot_labels = one_hot([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

    #print(create_network(X[:70], Y[:70], test_X[:70]))
    print(class_acc(create_network(X, Y, test_X[:1000]), test_Y))

main()