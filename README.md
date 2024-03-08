# COP3530-Project-3

Features:
● Safest to Least Safe State Identification: Provide users with information on the safest
and least safest states based on historical earthquake data.
● Earthquake Location Visualization: Utilize a mapping library to show earthquake
locations on a map.
● Sorting and filtering: Allow users to sort earthquakes by magnitude and select a date
range to analyze earthquake occurrences.

Strategy:
● Utilize an unordered set to store state names for efficient filtering when reading in
earthquake data specific to states.
● Create an unordered map with earthquake IDs as keys. Each earthquake ID uniquely
identifies an earthquake event, and its associated value is a structured data object, such
as a tuple or a struct, containing comprehensive earthquake information, including year,
latitude, longitude, magnitude, and other relevant details.
● Develop algorithms to process datasets with a focus on analyzing earthquake
magnitudes and frequencies. This includes algorithms, such as min and max heaps, to
identify states with the highest and lowest earthquake risks based on historical data.
● Implement sorting and filtering algorithms that allow users to view earthquakes based on
specific criteria such as magnitude ranges and date intervals.
● Integrate mapping functionalities to visually represent earthquake data on a
geographical map.
