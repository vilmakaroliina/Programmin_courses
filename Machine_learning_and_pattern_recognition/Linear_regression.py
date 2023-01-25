import matplotlib.pyplot as plt
import numpy as np

def class_acc(pred, gt):
    correct_labels = 0
    for i in range(0, len(pred)):
        if pred[i] == gt[i]:
            correct_labels += 1

    correct = correct_labels/len(pred)*100
    return correct

def my_line(x, y):
    sumx=0;
    sumy=0;
    sumxy=0;
    sumx2 = 0;
    for i in range(0, len(x)):
        sumx = sumx + x[i]
        sumx2 = sumx2 + x[i]*x[i]
        sumy = sumy + y[i]
        sumxy = sumxy + x[i]*y[i]

    b = (sumx2*sumy-sumx*sumxy)/(len(x)*sumx2-sumx*sumx)
    a = (sumxy - b *sumx)/sumx2
    return a, b

def baseline(data_set):
    print("Computing baseline regression")
    y_train = np.loadtxt('y_train.dat')
    mean = np.mean(y_train)

    mae = np.mean(np.abs(y_train-mean))

    return mae

def mae(y_train, y_test):
    mae = np.mean(np.abs(y_train-y_test))
    return mae

def linear_regeression(x_data, a, b):
    all_ys = []
    for i in range(len(x_data)):
        ys = a * np.mean(x_data[i]) + b
        all_ys.append(ys)


    return all_ys

def main():
    x_train = np.loadtxt('X_train.dat')
    y_train = np.loadtxt('y_train.dat')
    x_test = np.loadtxt('X_test.dat')
    y_test = np.loadtxt('y_test.dat')

    print("Baseline accuracy (MAE): ", baseline(np.array(y_train)))
    a, b = my_line(np.array(x_train), np.array(y_train))
    all_ys = np.array(linear_regeression(x_train, a, b))
    #all_ys = all_ys.reshape(404)
    mae(y_train, all_ys)



main()