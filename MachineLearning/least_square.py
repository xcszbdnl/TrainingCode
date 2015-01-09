from numpy import *
from pylab import *
def least_square(x, y):
    sums_xi_yi = 0.0
    sums_xi_square = 0.0
    sums_xi = 0.0
    sums_yi = 0.0
    for i in range(0, len(x)):
        sums_xi += x[i][1]
        sums_yi += y[i]
        sums_xi_yi += x[i][1] * y[i]
        sums_xi_square += x[i][1] * x[i][1]
    a = (sums_xi_yi - sums_xi * sums_yi / len(x)) / (sums_xi_square - sums_xi * sums_xi / len(x))
    b = 0.0
    for i in range(0, len(x)):
        b += y[i] - a * x[i][1]
    b /= len(x)
    another_x = []
    another_y = []
    for i in range(len(x)):
        another_x.append(x[i][1])
        another_y.append(b * x[i][0] + a * x[i][1])
    plot(another_x, y, 'o')
    print another_y
    plot(another_x, another_y)
    show()
    return a, b
        
def dist(x,y):
    list = (x - y).transpose().tolist()
    dist = 0.0
    for i in range(len(list[0])):
        dist += list[0][i] * list[0][i]
    return dist / 2


def gradient_descent_matrix(x, y):
    learn_rate = 0.001
    x_matrix = mat(x)
    y_matrix = mat(y).transpose()
    m, n = shape(x)
    weights = zeros((n,1))
    cycles = 100
    for i in range(cycles):
        print "dist is %f" % (dist(x_matrix * weights, y))
        h = x_matrix * weights
        error = y_matrix - h
        #weights = weights + learn_rate * x_matrix.transpose() * error
        weights = weights - learn_rate * (x_matrix.transpose() * x_matrix * weights - x_matrix.transpose() * y_matrix)
        print "%d times iterator:" % (i)
        print weights
    return weights.tolist()


def gradient_descent(x,y):
    theta = [1,1]
    learn_rate = 0.01
    cycles = 10
    temp=[1,1]
    for i in range(cycles):
        temp[0] = theta[0]
        temp[1] = theta[1]
        obj = 0.0
        for j in range(len(x)):
            dis = (theta[0] * x[j][0] + theta[1] * x[j][1] - y[j])
            dis *= dis
            obj += dis
        print "obj is %f" % (obj / 2 / len(x))
        for j in range(len(x[0])):
            gradient = 0.0;
            for k in range(len(x)):
                gradient += (x[k][0] * theta[0] + x[k][1] * theta[1] - y[k]) * x[k][j]
            temp[j] = temp[j] - gradient * learn_rate / len(x)
            print "gradient:%f" % gradient
        theta[0] = temp[0]
        theta[1] = temp[1]
        print "%d times iterator:" % i,
        print theta
    print "final theta",
    print theta
    """
    another_x = []
    another_y = []
    for i in range(len(x)):
        another_x.append(x[i][1])
        another_y.append(theta[0] * x[i][0] + theta[1] * x[i][1])
    plot(another_x, y, 'o')
    print another_y
    plot(another_x, another_y)
    show()
    least_square(x,y)
    """
    return theta


def test(x,y):
    theta = [0,0]
    learn_rate = 0.01
    cycles = 100
    for i in range(cycles):
        temp = theta
        for j in range(len(x)):
            error = 0.0;
            for k in range(len(x)):
                error += (y[k] - x[k][0] * theta[0] + x[k][1] * theta[1]) * x[k][j]
            temp[j] = temp[j] + error * learn_rate
        theta = temp
        print "%d times iterator:" % i,
        print theta
    return theta

def loadData():
    x,y=[],[]
    file = open('least_square_set.txt', 'r')
    for lines in file.readlines():
        a,b = lines.split()
        x.append([1,double(a)])
        y.append(double(b))
    return x, y

if __name__ == '__main__':
    x,y = loadData()
    gradient_descent(x,y)
    """
    x = []
    y = []
    for i in range(1,10):
        x.append([1,i])
        y.append(i)
    gradient_descent(x,y)
    """
