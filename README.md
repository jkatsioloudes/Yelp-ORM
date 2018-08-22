# Yelp - Object Relational Mapping (ORM)

## What is Object Relational Mapping?
Object Relational Mapping (ORM) is a technique for converting data between incompatible type systems using object-oriented programming languages. This creates, in effect, a "virtual object database" that can be used from within the programming language. There are both free and commercial packages available that perform object-relational mapping, although some programmers opt to construct their own ORM tools.

## What is ODB?
ODB is an object-relational modeling framework (https://www.codesynthesis.com/products/odb/doc/manual.xhtml) used as the main package behind this repository.

## Data Analytics

As a Proof of Concept, the following Data Analytics were extracted from our object representation:

* Finds the opening hours of all restaurants a user has rated

Acceps a single string parameter that designates a username and returns the hours as an array of strings.

* Calculates a histogram of all reviews for all businesses within an area

Areas are defined by latitude and longitude in a function called countStars.  The whole query is wrapped within an ODB query (called a view).

* Creates Microsoft's columnstore indices for selected columns

These are in essence, a DSM representation of selected columns from a single table by creating a columnstore index to benefit from caching.

## Performance Optimisations and Tradeoffs

* Vectors as element containers

A vector is an ordered collection of elementents that can be accessed by index but does not provide a built-in functionality to check for the presence of a specific element.  Iteration takes time but appending new elements is easy.

* Unordered Sets

This is similar to dictionaries that allow fast and efficient search for elements.  It is essentially a collection of elements wihtout a defined order but allows the checking for the presence of an element in constant time by making use of a hash-table with a built-in hash function and integrated conflict management.

* Performance Observations

Vectors are good for aggregation because they allow updates on the elements they contain because the aggregates become the elements of the vector while the positions are used as implicit keys.  However this requires to ensure that the size of the vector is greater than the index of the accessed element.  If the maximum group value is known when writing the program, the vector can be then constructed with a pre-specified space.

## Note
In this repo there exists a subset of my work, often intentionally broken or misleading to avoid disrespectful people from copying and
pasting.
