#include <iostream>
using namespace std;

// Function for Fractional Knapsack
double fractionalKnapsack(int weight[], int profit[], int n, int cap) {
    // Create an array to store profit/weight ratios
    double ratio[n];

    // Calculate the profit/weight ratio for each item
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)profit[i] / weight[i];
    }

    // Sort items based on the profit/weight ratio in descending order using temp for swapping
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                // Swap ratio
                double tempRatio = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = tempRatio;

                // Swap weight
                int tempWeight = weight[i];
                weight[i] = weight[j];
                weight[j] = tempWeight;

                // Swap profit
                int tempProfit = profit[i];
                profit[i] = profit[j];
                profit[j] = tempProfit;
            }
        }
    }

    double totalProfit = 0.0;
    int currentWeight = 0;

    // Greedily take items
    for (int i = 0; i < n; i++) {
        // If the entire item can fit into the knapsack
        if (currentWeight + weight[i] <= cap) {
            currentWeight += weight[i];
            totalProfit += profit[i];
        }
        // If only a fraction of the item can fit
        else {
            int remainingWeight = cap - currentWeight;
            totalProfit += profit[i] * ((double)remainingWeight / weight[i]);
            break; // No more items can be added after this
        }
    }

    return totalProfit;
}

int main() {
    int n, cap;
    cout << "Enter number of objects and knapsack capacity: ";
    cin >> n >> cap;

    int weight[n], profit[n];
    
    cout << "Enter weights: ";
    for (int i = 0; i < n; i++) cin >> weight[i];

    cout << "Enter profits: ";
    for (int i = 0; i < n; i++) cin >> profit[i];

    double maxProfit = fractionalKnapsack(weight, profit, n, cap);
    cout << "Maximum profit (Fractional Knapsack): " << maxProfit << endl;

    return 0;
}
