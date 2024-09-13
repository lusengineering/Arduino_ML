import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from micromlgen import port

# Laden des Datasets
data = pd.read_csv('/Users/luismarx/Documents/Python Code/LEDDATEN.txt', header=None)

# Aufteilen der Daten in Eingabe- und Ausgabedaten
X = data.iloc[:, :-1]  # Alle Spalten außer der letzten als Eingabedaten
y = data.iloc[:, -1]   # Die letzte Spalte als Ausgabedaten

# Aufteilen der Daten in Trainings- und Testsets
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Training des Modells (ohne Feature Selection)
clf = RandomForestClassifier(max_depth=3, random_state=42)
clf.fit(X_train, y_train)

# Vorhersage und Bewertung des Modells
y_pred = clf.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy}')

report = classification_report(y_test, y_pred, zero_division=0)
print('Classification Report:\n', report)

# Arduino Code exportieren (auskommentiert, falls benötigt)
arduino_code = open("ML_LED_Steuerung.h", mode="w+")
arduino_code.write(port(clf))
arduino_code.close()
