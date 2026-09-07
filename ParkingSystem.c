#include "MKL25Z4.h"

__asm void ParkingSystem(void) {
    LDR R0, =0x1A2B3      // Load the car number into R0
    MOVS R1, #3           // Load the parking duration (3 hours in this example) into R1

CalculateCharge
    CMP R1, #1            // Compare parking duration with 1 hour
    BLT Charge0_5         // If duration < 1 hour, jump to Charge0_5

    CMP R1, #2            // Compare parking duration with 2 hours
    BLT Charge0_95        // If duration < 2 hours, jump to Charge0_95

    CMP R1, #3            // Compare parking duration with 3 hours
    BLT Charge1_7         // If duration < 3 hours, jump to Charge1_7

    CMP R1, #4            // Compare parking duration with 4 hours
    BLT Charge2_6         // If duration < 4 hours, jump to Charge2_6

    LDR R2, =350          // If duration >= 4 hours, set charge to 3.50 euros (350 cents)
    B Payment             // Jump to Payment section

Charge0_5
    MOVS R2, #50          // Set charge to 0.50 euros (50 cents)
    B Payment             // Jump to Payment section

Charge0_95
    MOVS R2, #95          // Set charge to 0.95 euros (95 cents)
    B Payment             // Jump to Payment section

Charge1_7
    MOVS R2, #170         // Set charge to 1.70 euros (170 cents)
    B Payment             // Jump to Payment section

Charge2_6
    LDR R2, =260          // Set charge to 2.60 euros (260 cents)

Payment
    MOVS R3, #0           // Initialize the payment amount to 0 (R3)

PaymentLoop
    MOVS R6, #200         // Each payment input is 2 euro (200 cents)
    ADDS R3, R3, R6       // Add the input amount to the total payment (R3)
    CMP R3, R2            // Compare the total payment with the required charge (R2)
    BEQ Success           // If the payment matches the charge, jump to Success
    BHI Refund            // If the payment exceeds the charge, jump to Refund
    BLT Remaining         // If the payment is less than the charge, jump to Remaining

Remaining
    SUBS R4, R2, R3       // Calculate the remaining amount to be paid (R4 = R2 - R3)
    B PaymentLoop         // Loop back to PaymentLoop to request additional input

Refund
    SUBS R5, R3, R2       // Calculate the refund amount (R5 = R3 - R2)
    B Success             // Continue to the Success section

Success
    MOVS R7, #1           // Indicate successful payment by setting R7 to 1
    BX LR                 // Return from the function
}

int main(void) {
    ParkingSystem();       // Call the ParkingSystem function
    return 0;              // End the program
}
