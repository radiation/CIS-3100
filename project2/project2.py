import math
import csv
from random import shuffle
import time

# Define a class to handle data operations
class DataHandler:
    def __init__(self, filepath):
        # Constructor to initialize the filepath
        self.filepath = filepath

    def read_csv(self):
        # Read data from a CSV file and store it in a list
        with open(self.filepath, 'r') as file:
            csv_reader = csv.reader(file)
            next(csv_reader)  # Skip the header row
            dataset = [row for row in csv_reader]
        return dataset

    # Shuffle and split the dataset into training and testing sets based on the test_size
    def train_test_split(self, dataset, test_size):
        shuffle(dataset)
        split_index = int(len(dataset) * (1 - test_size))
        return dataset[:split_index], dataset[split_index:]

    # Separate features & labels from the dataset and convert feature values to floats for computation
    # Assumes the last column contains the labels
    def separate_features_labels(self, dataset):
        features = [list(map(float, data[1:-1])) for data in dataset]
        labels = [data[-1] for data in dataset]
        return features, labels

# Define a base class for ML classifiers so we can reuse the predict & report methods
class MLClassifier:
    def __init__(self):
        # Initialize the classifier
        pass

    def predict(self, x):
        # Predict a list of feature sets
        return [self.predict_single(features) for features in x]

    # Generate a classification report for the predictions
    def classification_report(self, y_true, y_pred):
        unique_labels = set(y_true)
        report = {}
        for label in unique_labels:

            # Calculate true positives, false positives, false negatives, and true negatives
            tp = sum(1 for i in range(len(y_true)) if y_true[i] == label and y_pred[i] == label)
            fp = sum(1 for i in range(len(y_true)) if y_true[i] != label and y_pred[i] == label)
            fn = sum(1 for i in range(len(y_true)) if y_true[i] == label and y_pred[i] != label)
            tn = sum(1 for i in range(len(y_true)) if y_true[i] != label and y_pred[i] != label)

            # Calculate precision, recall, and F1-score for each class
            precision = tp / (tp + fp) if tp + fp > 0 else 0
            recall = tp / (tp + fn) if tp + fn > 0 else 0
            f1 = 2 * (precision * recall) / (precision + recall) if precision + recall > 0 else 0
            accuracy = (tp + tn) / len(y_true)

            report[label] = {
                'Precision': precision,
                'Recall': recall,
                'F1-score': f1,
                'Accuracy': accuracy
            }

        return report

# Naive Bayes classifier
class NaiveBayesClassifier(MLClassifier):
    def __init__(self):
        # Dicts for mean, stdev, and class probabilities
        self.means = {}
        self.stds = {}
        self.class_probabilities = {}

    def fit(self, x, y):
        # Train the classifier by calculating the class probabilities
        # and the means and standard deviations for each feature
        self._calculate_class_probabilities(y)
        self._calculate_means_stds(x, y)

    def _calculate_class_probabilities(self, y):
        # Calculate the probability of each class based on label frequency
        class_counts = {label: y.count(label) for label in set(y)}
        total_count = len(y)
        self.class_probabilities = {label: count / total_count for label, count in class_counts.items()}

    def _calculate_means_stds(self, x, y):
        # Calculate the mean and standard deviation for each class and each feature
        for label in self.class_probabilities:
            # Extract features for instances of the current class
            label_features = [x[i] for i in range(len(x)) if y[i] == label]
            # Calculate mean and standard deviation for each feature
            self.means[label] = [sum(f) / len(f) for f in zip(*label_features)]
            self.stds[label] = [math.sqrt(sum([(x - mean)**2 for x in f]) / len(f)) for mean, f in zip(self.means[label], zip(*label_features))]

    def predict_single(self, input_features):
        # Predict the class of a single feature set
        probabilities = {}
        for label, _ in self.means.items():
            # Start with the prior probability of the class
            probabilities[label] = self.class_probabilities[label]
            # Multiply by the probability of each feature
            for i, feature in enumerate(input_features):
                probabilities[label] *= self._calculate_probability(feature, self.means[label][i], self.stds[label][i])
        # Return the class with the highest probability
        return max(probabilities, key=probabilities.get)

    def _calculate_probability(self, x, mean, std):
        # Calculate the probability of a feature value with a Gaussian distribution
        exponent = math.exp(-(math.pow(x-mean,2)/(2*math.pow(std,2))))
        return (1 / (math.sqrt(2*math.pi) * std)) * exponent

    def __str__(self):
        return "Naive Bayes"

# K Nearest Neighbors classifier
class KNNClassifier(MLClassifier):
    def __init__(self, k=5):
        # Initialize the number of neighbors to consider
        self.k = k

    def fit(self, x, y):
        # Train the classifier by storing the training data
        self.x_train = x
        self.y_train = y

    def predict_single(self, input_features):
        # Predict the class of a single feature set
        distances = []
        for i, x in enumerate(self.x_train):
            # Calculate the Euclidean distance between the input features and each training instance
            distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(input_features, x)]))
            distances.append((distance, self.y_train[i]))
        # Sort the distances and get the k nearest neighbors
        distances.sort(key=lambda x: x[0])
        neighbors = distances[:self.k]
        # Count the class occurrences in the neighbors
        counts = {}
        for neighbor in neighbors:
            if neighbor[1] in counts:
                counts[neighbor[1]] += 1
            else:
                counts[neighbor[1]] = 1
        # Return the class with the highest count
        return max(counts, key=counts.get)

    def __str__(self):
        return "K Nearest Neighbors"

# Support Vector Machine classifier
class SVMClassifier(MLClassifier):
    def __init__(self, learning_rate=0.001, lambda_param=0.01):
        self.learning_rate = learning_rate
        self.lambda_param = lambda_param
        self.w = None
        self.b = None

    def fit(self, X, y):
        n_samples, n_features = len(X), len(X[0])

        # Initialize weights and bias
        self.w = [0.0 for _ in range(n_features)]
        self.b = 0.0

        # Convert labels to +1 and -1 for binary classification
        y = [1 if label == "Good" else -1 for label in y]

        # Gradient descent
        for _ in range(n_samples):
            for idx, x_i in enumerate(X):
                condition = y[idx] * (self.dot_product(x_i, self.w) - self.b) >= 1
                if condition:
                    for j in range(n_features):
                        self.w[j] -= self.learning_rate * (2 * self.lambda_param * self.w[j])
                else:
                    for j in range(n_features):
                        self.w[j] -= self.learning_rate * (2 * self.lambda_param * self.w[j] - x_i[j] * y[idx])
                    self.b -= self.learning_rate * y[idx]

    def predict_single(self, input_features):
        approx = self.dot_product(input_features, self.w) - self.b
        return "Good" if approx >= 0 else "Bad"

    def dot_product(self, x1, x2):
        return sum(x1[i] * x2[i] for i in range(len(x1)))

    def __str__(self):
        return "Support Vector Machine"

def main():

    # Define the test size for the train_test_split method so we can display the split
    TEST_SIZE = 0.2
    print(f"\nTest size: {TEST_SIZE}")

    # Define the path to the CSV file containing the Iris dataset
    filepath = 'banana_quality.csv'

    # Initialize the data handler with the filepath
    # This object will handle all data operations
    data_handler = DataHandler(filepath)

    # Read the dataset from the CSV file using the read_csv method
    # The dataset is returned as a list of lists, where each sublist is a row from the file
    dataset = data_handler.read_csv()

    # Split the dataset into training and testing parts using the train_test_split method
    # Default split is 80% training and 20% testing
    train_set, test_set = data_handler.train_test_split(dataset, TEST_SIZE)

    # Separate features and labels for the training set
    # train_features will contain the data attributes, and train_labels will contain the target labels
    train_features, train_labels = data_handler.separate_features_labels(train_set)

    # Separate features and labels for the testing set
    # This setup mirrors the training separation
    test_features, test_labels = data_handler.separate_features_labels(test_set)

    # Iterate over the classifiers to compare their performance
    for classifier in [NaiveBayesClassifier(), KNNClassifier(), SVMClassifier()]:

        print(f"\n{classifier}:\n")

        start_time = time.time()
        classifier.fit(train_features, train_labels)
        fit_time = time.time() - start_time

        start_time = time.time()
        predictions = classifier.predict(test_features)
        predict_time = time.time() - start_time

        report = classifier.classification_report(test_labels, predictions)

        for label, metrics in report.items():
            print(f"\tClass {label}:")
            for metric, value in metrics.items():
                print(f"\t\t{metric}: {value:.2f}")
            print()

        print(f"\tFit time: {fit_time:.4f}s")
        print(f"\tPrediction time: {predict_time:.4f}s")

    print()

# This block checks if this script is the main program and runs the main function
if __name__ == "__main__":
    main()