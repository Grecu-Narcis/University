# Supermarket inventory
### Requirement:
There are several types of products, each having a known, constant, unit price. In the beginning, we know the quantity of each product.
We must keep track of the quantity of each product, the amount of money (initially zero), and the list of bills, corresponding to sales. Each bill is a list of items and quantities sold in a single operation, and their total price.
We have sale operations running concurrently, on several threads. Each sale decreases the amounts of available products (corresponding to the sold items), increases the amount of money, and adds a bill to a record of all sales.
From time to time, as well as at the end, an inventory check operation shall be run. It shall check that all the sold products and all the money are justified by the recorded bills.
Two sales involving distinct products must be able to update their quantities independently (without having to wait for the same mutex).

### Approach:

- each **product** has an associated mutex, such that only one thread can change a given product at a certain moment.
- **totalAmount** in **SalesService** is protected with a mutex.
- in **BillRepository**, add operation is synchronized on **bills** list.
- each thread iterates over the products, each product having a 75% chance to be chosen.
- if a product is chosen, the corresponding lock is achieved (or thread waits to achieve), a random quantity is taken and after updating new quantity of product the lock is released.

### Tests:
| Threads | Sales  | Time (ms) |
|---------|--------|-----------|
| 1       | 10     | 51        |
| 1       | 100    | 15        |
| 1       | 1000   | 18        |
| 1       | 10000  | 41        |
| 1       | 100000 | 254       |
| 2       | 10     | 7         |
| 2       | 100    | 11        |
| 2       | 1000   | 11        |
| 2       | 10000  | 84        |
| 2       | 100000 | 473       |
| 4       | 10     | 2         |
| 4       | 100    | 2         |
| 4       | 1000   | 13        |
| 4       | 10000  | 87        |
| 4       | 100000 | 832       |
| 8       | 10     | 2         |
| 8       | 100    | 2         |
| 8       | 1000   | 11        |
| 8       | 10000  | 109       |
| 8       | 100000 | 1081      |
| 16      | 10     | 3         |
| 16      | 100    | 3         |
| 16      | 1000   | 11        |
| 16      | 10000  | 107       |
| 16      | 100000 | 1075      |