#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

// Simple Vehicle structure
struct Vehicle {
    string plate;
    string type;
    string color;
    int slot;
    bool isParked;
    float charges;
    float fine;
    string paymentStatus;
    int ticket;
};

// Global arrays
string vehiclePlates[200];
string vehicleTypes[200];
string vehicleColors[200];
int parkingSlots[200];
int entryHours[200];
int entryMinutes[200];
string entryDates[200];
int exitHours[200];
int exitMinutes[200];
float parkingCharges[200];
float fineAmounts[200];
string paymentStatuses[200];
bool isParked[200];
int ticketNumbers[200];

// Simple slot arrays
bool slotOccupied[50];
int slotVehicles[50];

int totalVehicles = 0;
int totalSlots = 30;
float totalRevenue = 0.0;
int currentTicket = 1000;

// Function declarations
void displayLoginMenu();
bool login();
void initializeSystem();
void displayMainMenu();
void parkVehicle();
void removeVehicle();
void showParkingStatus();
void searchVehicle();
void showAllVehicles();
void modifyVehicle();
void calculateCharges();
void generateReport();
void showAvailableSlots();
void showVehicleTypes();
void showParkingRates();
void applyFine();
void showEntryInfo();
void showExitInfo();
void processPayment();
void checkPayment();
void showAllPayments();
void waitForEnter();
int findEmptySlot();
string getCurrentDate();
void printTicket(int index);
void printReceipt(int index, int hours, float total);
int calculateHours(int entryH, int entryM, int exitH, int exitM);
float calculateFee(int hours, string type);

// Main function
int main() {
    displayLoginMenu();
    return 0;
}

// Display login menu
void displayLoginMenu() {
    int choice;
    
    do {
        cout << "\n\n=========================================\n";
        cout << "          PARKING SYSTEM LOGIN\n";
        cout << "=========================================\n";
        cout << "   1. Login\n";
        cout << "   2. Exit\n";
        cout << "=========================================\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                if (login()) {
                    initializeSystem();
                    
                    cout << "\n=========================================\n";
                    cout << " Welcome to ANZ Parking Management System\n";
                    cout << "            OPEN: 24/7\n";
                    cout << "=========================================\n\n";
                    
                    int menuChoice;
                    do {
                        displayMainMenu();
                        cout << "Enter choice (1-18): ";
                        cin >> menuChoice;
                        
                        switch(menuChoice) {
                            case 1: parkVehicle(); break;
                            case 2: removeVehicle(); break;
                            case 3: showParkingStatus(); break;
                            case 4: searchVehicle(); break;
                            case 5: showAllVehicles(); break;
                            case 6: modifyVehicle(); break;
                            case 7: calculateCharges(); break;
                            case 8: generateReport(); break;
                            case 9: showAvailableSlots(); break;
                            case 10: showVehicleTypes(); break;
                            case 11: showParkingRates(); break;
                            case 12: applyFine(); break;
                            case 13: showEntryInfo(); break;
                            case 14: showExitInfo(); break;
                            case 15: processPayment(); break;
                            case 16: checkPayment(); break;
                            case 17: showAllPayments(); break;
                            case 18: 
                                cout << "\nThank you for using ANZ Parking System!\n";
                                cout << "Goodbye!\n";
                                break;
                            default: cout << "Invalid choice!\n";
                        }
                        
                        if (menuChoice != 18) waitForEnter();
                    } while (menuChoice != 18);
                    
                    return;
                }
                break;
            case 2:
                cout << "\nExiting program. Goodbye!\n";
                exit(0);
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice != 2);
}

// Login function
bool login() {
    string id, pass;
    int attempts = 0;
    
    do {
        cout << "\n\n=========================================\n";
        cout << "           LOGIN PANEL\n";
        cout << "=========================================\n";
        
        cout << "User ID (admin/user): ";
        cin >> id;
        cout << "Password: ";
        cin >> pass;
        
        if ((id == "admin" && pass == "admin123") || 
            (id == "user" && pass == "user123")) {
            cout << "\n=========================================\n";
            cout << "     LOGIN SUCCESSFUL!\n";
            cout << "     Welcome, " << id << "!\n";
            cout << "=========================================\n";
            return true;
        } else {
            cout << "\n=========================================\n";
            cout << "  INCORRECT ID/PASSWORD!\n";
            cout << "  Please try again.\n";
            cout << "=========================================\n";
            attempts++;
        }
    } while (attempts < 3);
    
    cout << "Too many failed attempts!\n";
    return false;
}

// Initialize system
void initializeSystem() {
    srand(time(0));
    for (int i = 0; i < totalSlots; i++) {
        slotOccupied[i] = false;
        slotVehicles[i] = -1;
    }
    cout << "\nParking system initialized!\n";
    cout << "Total slots: " << totalSlots << "\n";
}

// Display main menu
void displayMainMenu() {
    cout << "\n\n=========================================\n";
    cout << "        PARKING SYSTEM MAIN MENU\n";
    cout << "=========================================\n";
    cout << "   1.  Park New Vehicle\n";
    cout << "   2.  Remove Vehicle (Auto Exit Time)\n";
    cout << "   3.  Display Parking Status\n";
    cout << "   4.  Search Vehicle\n";
    cout << "   5.  Show All Vehicles\n";
    cout << "   6.  Modify Vehicle Details\n";
    cout << "   7.  Calculate Parking Charges (Auto)\n";
    cout << "   8.  Generate Daily Report\n";
    cout << "   9.  Show Available Slots\n";
    cout << "   10. Show Vehicle Types\n";
    cout << "   11. Show Parking Rates\n";
    cout << "   12. Apply Fine\n";
    cout << "   13. ENTRY DATA Information\n";
    cout << "   14. EXIT DATA Information\n";
    cout << "   15. Process Payment\n";
    cout << "   16. Check/Update Payment Status\n";
    cout << "   17. View All Payment Statuses\n";
    cout << "   18. Logout & Exit Program\n";    
    cout << "=========================================\n";
}

// Park new vehicle
void parkVehicle() {
    cout << "\n\n=========================================\n";
    cout << "          PARK NEW VEHICLE\n";
    cout << "=========================================\n";
    
    int emptySlot = findEmptySlot();
    if (emptySlot == -1) {
        cout << "\nSorry! Parking is full.\n";
        return;
    }
    
    cout << "\nAvailable parking slot: " << (emptySlot + 1) << "\n";
    
    cout << "\n--- ENTER VEHICLE DETAILS ---\n";
    
    cout << "\nSelect Vehicle Type:\n";
    cout << "1. Car\n";
    cout << "2. Motorcycle\n";
    cout << "3. Van\n";
    cout << "4. Truck\n";
    cout << "5. SUV\n";
    cout << "Enter type (1-5): ";
    
    int typeChoice;
    cin >> typeChoice;
    
    string type;
    switch(typeChoice) {
        case 1: type = "Car"; break;
        case 2: type = "Motorcycle"; break;
        case 3: type = "Van"; break;
        case 4: type = "Truck"; break;
        case 5: type = "SUV"; break;
        default: type = "Car";
    }
    
    cout << "Enter Vehicle Plate Number: ";
    cin.ignore();
    getline(cin, vehiclePlates[totalVehicles]);
    
    cout << "Enter Vehicle Color: ";
    getline(cin, vehicleColors[totalVehicles]);
    
    // Get current time automatically
    time_t now = time(0);
    tm* ltm = localtime(&now);
    entryHours[totalVehicles] = ltm->tm_hour;
    entryMinutes[totalVehicles] = ltm->tm_min;
    entryDates[totalVehicles] = getCurrentDate();
    
    // Store vehicle data
    vehicleTypes[totalVehicles] = type;
    parkingSlots[totalVehicles] = emptySlot + 1;
    isParked[totalVehicles] = true;
    parkingCharges[totalVehicles] = 0.0;
    fineAmounts[totalVehicles] = 0.0;
    paymentStatuses[totalVehicles] = "Not Due";
    exitHours[totalVehicles] = 0;
    exitMinutes[totalVehicles] = 0;
    ticketNumbers[totalVehicles] = currentTicket++;
    
    // Update slot
    slotOccupied[emptySlot] = true;
    slotVehicles[emptySlot] = totalVehicles;
    
    totalVehicles++;
    
    cout << "\nVehicle parked successfully!\n";
    printTicket(totalVehicles - 1);
}

// Find empty slot
int findEmptySlot() {
    for (int i = 0; i < totalSlots; i++) {
        if (!slotOccupied[i]) {
            return i;
        }
    }
    return -1;
}

// Get current date
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%d/%m/%Y", ltm);
    return string(date);
}

// Print parking ticket
void printTicket(int index) {
    cout << "\n=========================================\n";
    cout << "        PARKING TICKET\n";
    cout << "=========================================\n";
    cout << "  Ticket Number:   TKT-" << ticketNumbers[index] << "\n";
    cout << "  Vehicle Number:  " << vehiclePlates[index] << "\n";
    cout << "  Vehicle Type:    " << vehicleTypes[index] << "\n";
    cout << "  Vehicle Color:   " << vehicleColors[index] << "\n";
    cout << "  Parking Slot:    " << parkingSlots[index] << "\n";
    cout << "  Entry Date:      " << entryDates[index] << "\n";
    cout << "  Entry Time:      " << entryHours[index] << ":" 
         << setw(2) << setfill('0') << entryMinutes[index] << "\n";
    cout << "=========================================\n";
    cout << "      Keep this ticket for exit!\n";
    cout << "=========================================\n\n";
}

// Remove vehicle
void removeVehicle() {
    cout << "\n\n=========================================\n";
    cout << "          REMOVE VEHICLE\n";
    cout << "=========================================\n";
    
    int slotNumber;
    cout << "\nEnter parking slot number: ";
    cin >> slotNumber;
    
    if (slotNumber < 1 || slotNumber > totalSlots) {
        cout << "\nError: Invalid slot number!\n";
        return;
    }
    
    int slotIndex = slotNumber - 1;
    if (!slotOccupied[slotIndex]) {
        cout << "\nSlot " << slotNumber << " is empty!\n";
        return;
    }
    
    int vehicleIndex = slotVehicles[slotIndex];
    cout << "\nVehicle found in slot " << slotNumber << "\n";
    cout << "Plate: " << vehiclePlates[vehicleIndex] << "\n";
    
    // Automatically record exit time
    time_t now = time(0);
    tm* ltm = localtime(&now);
    exitHours[vehicleIndex] = ltm->tm_hour;
    exitMinutes[vehicleIndex] = ltm->tm_min;
    
    // Calculate parking hours
    int parkingHours = calculateHours(
        entryHours[vehicleIndex],
        entryMinutes[vehicleIndex],
        exitHours[vehicleIndex],
        exitMinutes[vehicleIndex]
    );
    
    // Calculate charges
    float charges = calculateFee(parkingHours, vehicleTypes[vehicleIndex]);
    float totalAmount = charges + fineAmounts[vehicleIndex];
    
    cout << "\n--- AUTO CALCULATION ---\n";
    cout << "Entry Time: " << entryHours[vehicleIndex] << ":" 
         << setw(2) << setfill('0') << entryMinutes[vehicleIndex] << "\n";
    cout << "Exit Time:  " << exitHours[vehicleIndex] << ":" 
         << setw(2) << setfill('0') << exitMinutes[vehicleIndex] << " (Auto)\n";
    cout << "Total Hours: " << parkingHours << "\n";
    cout << "Parking Charges: Rs." << charges << "\n";
    cout << "Fine Amount: Rs." << fineAmounts[vehicleIndex] << "\n";
    cout << "Total Amount: Rs." << totalAmount << "\n";
    
    cout << "\nConfirm removal? (1 = Yes, 0 = No): ";
    int confirm;
    cin >> confirm;
    
    if (confirm != 1) {
        cout << "\nRemoval cancelled.\n";
        return;
    }
    
    // Update vehicle status
    parkingCharges[vehicleIndex] = charges;
    paymentStatuses[vehicleIndex] = "Unpaid";
    isParked[vehicleIndex] = false;
    
    // Free the slot
    slotOccupied[slotIndex] = false;
    slotVehicles[slotIndex] = -1;
    
    printReceipt(vehicleIndex, parkingHours, totalAmount);
    cout << "\nVehicle removed successfully!\n";
}

// Calculate parking hours
int calculateHours(int entryH, int entryM, int exitH, int exitM) {
    int totalMinutesEntry = entryH * 60 + entryM;
    int totalMinutesExit = exitH * 60 + exitM;
    
    if (totalMinutesExit < totalMinutesEntry) {
        totalMinutesExit += 24 * 60;
    }
    
    int difference = totalMinutesExit - totalMinutesEntry;
    int hours = difference / 60;
    if (difference % 60 > 0) hours++;
    if (hours < 1) hours = 1;
    return hours;
}

// Calculate parking fee
float calculateFee(int hours, string type) {
    float hourlyRate = 50.0;
    if (type == "Car" || type == "SUV") {
        hourlyRate = 50.0;
    } else if (type == "Motorcycle") {
        hourlyRate = 20.0;
    } else if (type == "Van") {
        hourlyRate = 70.0;
    } else if (type == "Truck") {
        hourlyRate = 100.0;
    }
    return hourlyRate * hours;
}

// Print receipt
void printReceipt(int index, int hours, float totalCharge) {
    cout << "\n\n=========================================\n";
    cout << "        PARKING PAYMENT RECEIPT\n";
    cout << "=========================================\n";
    cout << "  Ticket Number:    TKT-" << ticketNumbers[index] << "\n";
    cout << "  Vehicle Number:   " << vehiclePlates[index] << "\n";
    cout << "  Vehicle Type:     " << vehicleTypes[index] << "\n";
    cout << "  Vehicle Color:    " << vehicleColors[index] << "\n";
    cout << "  Parking Slot:     " << parkingSlots[index] << "\n";
    cout << "  Entry Date:       " << entryDates[index] << "\n";
    cout << "  Entry Time:       " << entryHours[index] << ":" 
         << setw(2) << setfill('0') << entryMinutes[index] << "\n";
    cout << "  Exit Time:        " << exitHours[index] << ":" 
         << setw(2) << setfill('0') << exitMinutes[index] << "\n";
    cout << "  Parking Hours:    " << hours << "\n";
    cout << "  Parking Charges:  Rs." << parkingCharges[index] << "\n";
    cout << "  Fine Amount:      Rs." << fineAmounts[index] << "\n";
    cout << "  Total Amount:     Rs." << totalCharge << "\n";
    cout << "  Payment Status:   " << paymentStatuses[index] << "\n";
    cout << "=========================================\n";
}

// Show parking status
void showParkingStatus() {
    cout << "\n\n=========================================\n";
    cout << "     CURRENT PARKING STATUS\n";
    cout << "=========================================\n";
    cout << "Slot\tStatus\t\tVehicle Number\tType\n";
    
    int available = 0;
    int occupied = 0;
    for (int i = 0; i < totalSlots; i++) {
        cout << setw(2) << (i+1) << "\t";
        if (slotOccupied[i]) {
            cout << "Occupied\t";
            int vIndex = slotVehicles[i];
            if (vIndex != -1) {
                cout << vehiclePlates[vIndex] << "\t";
                cout << vehicleTypes[vIndex];
            }
            occupied++;
        } else {
            cout << "Available\t---\t\t---";
            available++;
        }
        cout << "\n";
    }
    cout << "\nSUMMARY: Available=" << available << ", Occupied=" << occupied << "\n";
}

// Wait for Enter
void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// Search vehicle
void searchVehicle() {
    cout << "\n\n=========================================\n";
    cout << "          SEARCH VEHICLE\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate) {
            cout << "\n--- VEHICLE FOUND ---\n";
            cout << "Ticket: TKT-" << ticketNumbers[i] << "\n";
            cout << "Plate: " << vehiclePlates[i] << "\n";
            cout << "Type: " << vehicleTypes[i] << "\n";
            cout << "Color: " << vehicleColors[i] << "\n";
            cout << "Slot: " << parkingSlots[i] << "\n";
            cout << "Status: " << (isParked[i] ? "Parked" : "Exited") << "\n";
            cout << "Entry Date: " << entryDates[i] << "\n";
            cout << "Entry Time: " << entryHours[i] << ":" 
                 << setw(2) << setfill('0') << entryMinutes[i] << "\n";
            
            if (!isParked[i]) {
                cout << "Exit Time: " << exitHours[i] << ":" 
                     << setw(2) << setfill('0') << exitMinutes[i] << "\n";
                cout << "Parking Charges: Rs." << parkingCharges[i] << "\n";
                cout << "Fine: Rs." << fineAmounts[i] << "\n";
                cout << "Total: Rs." << (parkingCharges[i] + fineAmounts[i]) << "\n";
                cout << "Payment Status: " << paymentStatuses[i] << "\n";
            }
            return;
        }
    }
    
    cout << "\nVehicle not found.\n";
}

// Show all vehicles
void showAllVehicles() {
    cout << "\n\n=========================================\n";
    cout << "       ALL VEHICLES INFORMATION\n";
    cout << "=========================================\n";
    
    if (totalVehicles == 0) {
        cout << "\nNo vehicles recorded.\n";
        return;
    }
    
    cout << "\nTotal Vehicles: " << totalVehicles << "\n\n";
    for (int i = 0; i < totalVehicles; i++) {
        cout << "Vehicle " << (i+1) << ":\n";
        cout << "  Ticket: TKT-" << ticketNumbers[i] << "\n";
        cout << "  Plate: " << vehiclePlates[i] << "\n";
        cout << "  Type: " << vehicleTypes[i] << "\n";
        cout << "  Color: " << vehicleColors[i] << "\n";
        cout << "  Slot: " << parkingSlots[i] << "\n";
        cout << "  Entry Date: " << entryDates[i] << "\n";
        cout << "  Entry Time: " << entryHours[i] << ":" 
             << setw(2) << setfill('0') << entryMinutes[i] << "\n";
        cout << "  Status: " << (isParked[i] ? "Parked" : "Exited") << "\n";
        
        if (!isParked[i]) {
            cout << "  Exit Time: " << exitHours[i] << ":" 
                 << setw(2) << setfill('0') << exitMinutes[i] << "\n";
            cout << "  Parking Charges: Rs." << parkingCharges[i] << "\n";
            cout << "  Fine: Rs." << fineAmounts[i] << "\n";
            cout << "  Total: Rs." << (parkingCharges[i] + fineAmounts[i]) << "\n";
            cout << "  Payment Status: " << paymentStatuses[i] << "\n";
        }
        cout << "------------------------\n";
    }
}

// Modify vehicle
void modifyVehicle() {
    cout << "\n\n=========================================\n";
    cout << "       MODIFY VEHICLE DETAILS\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate) {
            cout << "\nVehicle found. Current details:\n";
            cout << "1. Plate: " << vehiclePlates[i] << "\n";
            cout << "2. Type: " << vehicleTypes[i] << "\n";
            cout << "3. Color: " << vehicleColors[i] << "\n";
            
            cout << "\nWhat to modify?\n";
            cout << "1. Plate Number\n";
            cout << "2. Vehicle Type\n";
            cout << "3. Vehicle Color\n";
            cout << "Enter choice: ";
            
            int choice;
            cin >> choice;
            
            cin.ignore();
            if (choice == 1) {
                cout << "\nNew plate number: ";
                getline(cin, vehiclePlates[i]);
                cout << "Plate updated!\n";
            } else if (choice == 2) {
                cout << "\nSelect new type:\n";
                cout << "1. Car\n2. Motorcycle\n3. Van\n4. Truck\n5. SUV\n";
                cout << "Enter choice (1-5): ";
                int typeChoice;
                cin >> typeChoice;
                
                switch(typeChoice) {
                    case 1: vehicleTypes[i] = "Car"; break;
                    case 2: vehicleTypes[i] = "Motorcycle"; break;
                    case 3: vehicleTypes[i] = "Van"; break;
                    case 4: vehicleTypes[i] = "Truck"; break;
                    case 5: vehicleTypes[i] = "SUV"; break;
                }
                cout << "Type updated!\n";
            } else if (choice == 3) {
                cout << "\nNew color: ";
                getline(cin, vehicleColors[i]);
                cout << "Color updated!\n";
            } else {
                cout << "\nInvalid choice.\n";
            }
            return;
        }
    }
    
    cout << "\nVehicle not found.\n";
}

// Calculate charges
void calculateCharges() {
    cout << "\n\n=========================================\n";
    cout << "     CALCULATE PARKING CHARGES\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate && isParked[i]) {
            time_t now = time(0);
            tm* ltm = localtime(&now);
            int exitHour = ltm->tm_hour;
            int exitMinute = ltm->tm_min;
            
            cout << "\nVehicle found: " << vehiclePlates[i] << "\n";
            cout << "Parked in slot " << parkingSlots[i] << "\n";
            cout << "Entry: " << entryHours[i] << ":" 
                 << setw(2) << setfill('0') << entryMinutes[i] << "\n";
            cout << "Current: " << exitHour << ":" 
                 << setw(2) << setfill('0') << exitMinute << "\n";
            
            int hours = calculateHours(
                entryHours[i],
                entryMinutes[i],
                exitHour,
                exitMinute
            );
            
            float charges = calculateFee(hours, vehicleTypes[i]);
            
            cout << "\n--- CALCULATION ---\n";
            cout << "Hours: " << hours << "\n";
            cout << "Parking: Rs." << charges << "\n";
            cout << "Fine: Rs." << fineAmounts[i] << "\n";
            cout << "Total: Rs." << (charges + fineAmounts[i]) << "\n";
            return;
        }
    }
    
    cout << "\nVehicle not found or not parked.\n";
}

// Generate report
void generateReport() {
    cout << "\n\n=========================================\n";
    cout << "     DAILY SUMMARY REPORT\n";
    cout << "=========================================\n";
    
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    cout << "Report Date: " << getCurrentDate() << "\n";
    cout << "Report Time: " << ltm->tm_hour << ":" << ltm->tm_min << "\n\n";
    
    int parked = 0, exited = 0, paid = 0, unpaid = 0;
    float todayRevenue = 0.0, pending = 0.0;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (isParked[i]) {
            parked++;
        } else {
            exited++;
            float total = parkingCharges[i] + fineAmounts[i];
            if (paymentStatuses[i] == "Paid") {
                paid++;
                todayRevenue += total;
            } else {
                unpaid++;
                pending += total;
            }
        }
    }
    
    cout << "STATISTICS:\n";
    cout << "-----------\n";
    cout << "Total Slots: " << totalSlots << "\n";
    cout << "Available: " << (totalSlots - parked) << "\n";
    cout << "Parked: " << parked << "\n";
    cout << "Total Vehicles: " << totalVehicles << "\n";
    cout << "Exited: " << exited << "\n";
    cout << "Paid: " << paid << "\n";
    cout << "Unpaid: " << unpaid << "\n";
    cout << "Today's Revenue: Rs." << todayRevenue << "\n";
    cout << "Pending: Rs." << pending << "\n";
    cout << "Total Revenue: Rs." << totalRevenue << "\n";
}

// Show available slots
void showAvailableSlots() {
    cout << "\n\n=========================================\n";
    cout << "     AVAILABLE PARKING SLOTS\n";
    cout << "=========================================\n";
    
    int count = 0;
    cout << "\nAvailable slots: ";
    
    for (int i = 0; i < totalSlots; i++) {
        if (!slotOccupied[i]) {
            cout << (i+1) << " ";
            count++;
        }
    }
    
    if (count == 0) {
        cout << "None - Parking is FULL";
    }
    
    cout << "\n\nTotal available: " << count << "/" << totalSlots << "\n";
}

// Show vehicle types
void showVehicleTypes() {
    cout << "\n\n=========================================\n";
    cout << "     ALLOWED VEHICLE TYPES & RATES\n";
    cout << "=========================================\n";
    
    cout << "\n1. CAR - Rs.50 per hour\n";
    cout << "2. MOTORCYCLE - Rs.20 per hour\n";
    cout << "3. VAN - Rs.70 per hour\n";
    cout << "4. TRUCK - Rs.100 per hour\n";
    cout << "5. SUV - Rs.50 per hour\n";
}

// Show parking rates
void showParkingRates() {
    cout << "\n\n=========================================\n";
    cout << "     PARKING RATES INFORMATION\n";
    cout << "=========================================\n";
    
    cout << "\nHOURLY PARKING RATES:\n";
    cout << "---------------------\n";
    cout << "Car / SUV: Rs.50 per hour\n";
    cout << "Motorcycle: Rs.20 per hour\n";
    cout << "Van: Rs.70 per hour\n";
    cout << "Truck: Rs.100 per hour\n";
}

// Apply fine
void applyFine() {
    cout << "\n\n=========================================\n";
    cout << "         APPLY FINE TO VEHICLE\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate) {
            cout << "\n--- VEHICLE FOUND ---\n";
            cout << "Plate: " << vehiclePlates[i] << "\n";
            cout << "Type: " << vehicleTypes[i] << "\n";
            cout << "Current Fine: Rs." << fineAmounts[i] << "\n";
            
            cout << "\n--- SELECT FINE TYPE ---\n";
            cout << "1. Late Payment Fee - Rs.500\n";
            cout << "2. Lost Ticket - Rs.1000\n";
            cout << "3. Wrong Parking - Rs.700\n";
            cout << "4. Custom Fine\n";
            cout << "Enter choice (1-4): ";
            
            int choice;
            cin >> choice;
            
            float fine = 0.0;
            switch(choice) {
                case 1: fine = 500.0; break;
                case 2: fine = 1000.0; break;
                case 3: fine = 700.0; break;
                case 4: 
                    cout << "Enter fine amount: Rs.";
                    cin >> fine;
                    break;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            
            fineAmounts[i] += fine;
            
            cout << "\n--- FINE APPLIED ---\n";
            cout << "Vehicle: " << vehiclePlates[i] << "\n";
            cout << "Fine Added: Rs." << fine << "\n";
            cout << "Total Fine: Rs." << fineAmounts[i] << "\n";
            return;
        }
    }
    
    cout << "\nVehicle not found.\n";
}

// Show entry info
void showEntryInfo() {
    cout << "\n\n=========================================\n";
    cout << "     ENTRY DATA INFORMATION\n";
    cout << "=========================================\n";
    
    cout << "\nAUTOMATIC ENTRY PROCESS:\n";
    cout << "========================\n";
    cout << "1. System automatically records:\n";
    cout << "   - Entry Date (Current date: " << getCurrentDate() << ")\n";
    cout << "   - Entry Time (Current time: ";
    time_t now = time(0);
    tm* ltm = localtime(&now);
    cout << ltm->tm_hour << ":" << setw(2) << setfill('0') << ltm->tm_min << ")\n";
    cout << "   - Ticket Number (Auto-generated)\n";
    cout << "   - Parking Slot (Assigned automatically)\n";
    
    cout << "\n2. NO MANUAL TIME ENTRY:\n";
    cout << "   - Prevents time fraud\n";
    cout << "   - 100% accurate\n";
    cout << "   - No human error\n";
}

// Show exit info
void showExitInfo() {
    cout << "\n\n=========================================\n";
    cout << "     EXIT DATA INFORMATION\n";
    cout << "=========================================\n";
    
    cout << "\nAUTOMATIC EXIT PROCESS:\n";
    cout << "=======================\n";
    cout << "1. System automatically:\n";
    cout << "   - Records Exit Time (Current time: ";
    time_t now = time(0);
    tm* ltm = localtime(&now);
    cout << ltm->tm_hour << ":" << setw(2) << setfill('0') << ltm->tm_min << ")\n";
    cout << "   - Calculates parking hours\n";
    cout << "   - Computes charges\n";
    cout << "   - Adds fines if any\n";
    
    cout << "\n2. NO MANUAL CALCULATION:\n";
    cout << "   - Everything automatic\n";
    cout << "   - Based on entry/exit times\n";
    cout << "   - Receipt prints automatically\n";
}

// Process payment
void processPayment() {
    cout << "\n\n=========================================\n";
    cout << "     PROCESS PAYMENT FOR VEHICLE\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate && !isParked[i]) {
            float total = parkingCharges[i] + fineAmounts[i];
            
            cout << "\n--- VEHICLE PAYMENT DETAILS ---\n";
            cout << "Plate: " << vehiclePlates[i] << "\n";
            cout << "Ticket: TKT-" << ticketNumbers[i] << "\n";
            cout << "Parking: Rs." << parkingCharges[i] << "\n";
            cout << "Fine: Rs." << fineAmounts[i] << "\n";
            cout << "Total Due: Rs." << total << "\n";
            cout << "Status: " << paymentStatuses[i] << "\n";
            
            if (paymentStatuses[i] == "Paid") {
                cout << "\nAlready paid!\n";
                return;
            }
            
            cout << "\nProceed to payment? (1=Yes, 0=No): ";
            int proceed;
            cin >> proceed;
            
            if (proceed != 1) {
                cout << "\nPayment cancelled.\n";
                return;
            }
            
            cout << "\nPayment methods:\n";
            cout << "1. Cash\n";
            cout << "2. Card\n";
            cout << "3. Mobile\n";
            cout << "4. Cancel\n";
            cout << "Enter choice (1-4): ";
            
            int choice;
            cin >> choice;
            
            if (choice == 1 || choice == 2 || choice == 3) {
                paymentStatuses[i] = "Paid";
                totalRevenue += total;
                cout << "\nPayment successful!\n";
                cout << "Amount: Rs." << total << "\n";
                cout << "Status: Paid\n";
                cout << "Transaction ID: TXN" << (10000 + rand() % 90000) << "\n";
            }
            return;
        }
    }
    
    cout << "\nVehicle not found or still parked.\n";
}

// Check payment
void checkPayment() {
    cout << "\n\n=========================================\n";
    cout << "     CHECK & UPDATE PAYMENT STATUS\n";
    cout << "=========================================\n";
    
    string searchPlate;
    cout << "\nEnter plate number: ";
    cin >> searchPlate;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (vehiclePlates[i] == searchPlate && !isParked[i]) {
            float total = parkingCharges[i] + fineAmounts[i];
            
            cout << "\n--- VEHICLE PAYMENT DETAILS ---\n";
            cout << "Plate: " << vehiclePlates[i] << "\n";
            cout << "Ticket: TKT-" << ticketNumbers[i] << "\n";
            cout << "Parking: Rs." << parkingCharges[i] << "\n";
            cout << "Fine: Rs." << fineAmounts[i] << "\n";
            cout << "Total: Rs." << total << "\n";
            cout << "Status: " << paymentStatuses[i] << "\n";
            
            cout << "\n--- UPDATE PAYMENT ---\n";
            cout << "1. Mark as Paid\n";
            cout << "2. Mark as Unpaid\n";
            cout << "3. Cancel\n";
            cout << "Enter choice (1-3): ";
            
            int choice;
            cin >> choice;
            
            switch(choice) {
                case 1:
                    paymentStatuses[i] = "Paid";
                    totalRevenue += total;
                    cout << "\nUpdated to: PAID\n";
                    break;
                case 2:
                    paymentStatuses[i] = "Unpaid";
                    cout << "\nUpdated to: UNPAID\n";
                    break;
                case 3:
                    cout << "\nUpdate cancelled.\n";
                    break;
                default:
                    cout << "\nInvalid choice!\n";
            }
            return;
        }
    }
    
    cout << "\nVehicle not found or still parked.\n";
}

// Show all payments
void showAllPayments() {
    cout << "\n\n=========================================\n";
    cout << "     ALL VEHICLES PAYMENT STATUS\n";
    cout << "=========================================\n";
    
    if (totalVehicles == 0) {
        cout << "\nNo vehicles recorded.\n";
        return;
    }
    
    int parked = 0, paid = 0, unpaid = 0;
    float due = 0.0, collected = 0.0;
    
    for (int i = 0; i < totalVehicles; i++) {
        if (isParked[i]) {
            parked++;
        } else {
            float total = parkingCharges[i] + fineAmounts[i];
            if (paymentStatuses[i] == "Paid") {
                paid++;
                collected += total;
            } else {
                unpaid++;
                due += total;
            }
        }
    }
    
    cout << "\nPAYMENT STATUS REPORT:\n";
    cout << "=====================\n";
    cout << "Total Vehicles: " << totalVehicles << "\n";
    cout << "Currently Parked: " << parked << "\n";
    cout << "Exited & Paid: " << paid << "\n";
    cout << "Exited & Unpaid: " << unpaid << "\n";
    cout << "Amount Collected: Rs." << collected << "\n";
    cout << "Amount Due: Rs." << due << "\n";
}
