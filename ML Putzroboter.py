import numpy as np
import pandas as pd
from sklearn.feature_selection import SelectKBest
from sklearn.feature_selection import f_classif
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from micromlgen import port

# Laden des Datasets
data = pd.read_csv('/Users/luismarx/Documents/Python Code/data.txt', header=None)

# Entfernen der ersten und letzten zwei Spalten
data = data.iloc[:, 1:-3]

# Aufteilen der Daten in Eingabe- und Ausgabedaten
X = data.iloc[:, :-1]  # Alle Spalten außer der letzten als Eingabedaten
y = data.iloc[:, -1]   # Die letzte Spalte als Ausgabedaten

# Aufteilen der Daten in Trainings- und Testsets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Feature Selection
k = 5  # Wähle die besten 5 Features (Angepasst je nach Bedarf)
k_best = SelectKBest(score_func=f_classif, k=k)
k_best.fit(X_train, y_train)

# Ausgewählte Features
selected_feature_indices = k_best.get_support(indices=True)
print("Selected Feature Indices: ", selected_feature_indices)

# Training des Modells mit ausgewählten Features
clf = RandomForestClassifier(max_depth=3, random_state=42)
clf.fit(X_train.iloc[:, selected_feature_indices], y_train)

# Vorhersage und Bewertung des Modells
y_pred = clf.predict(X_test.iloc[:, selected_feature_indices])

accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy}')

report = classification_report(y_test, y_pred, zero_division=0)
print('Classification Report:\n', report)

#Arduino Code exportieren (auskommentiert, falls benötigt)
arduino_code = open("arduino_random_forest10.h", mode="w+")
arduino_code.write(port(clf))
arduino_code.close()
print("selected features: ", X.columns[selected_feature_indices])