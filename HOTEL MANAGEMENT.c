#include <stdio.h>
#include <string.h>

// GLOBAL DECLARATION
#define Max_roomQuant 75
#define Max_foodQuant 10
#define Max_FacilityQuant 5
float roomTotal[Max_roomQuant] = {0};

// --- PROTOTYPES ---
void displayRoomType(int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[]);
void displayMenuFood(int QuantFood, char nameFood[][20], float priceFood[]);
void displayFoodBills(int QuantFood, char nameFood[][20], float priceFood[], float QuantEachFood[], float *totAllFood); 
void displayMenuFacility(int QuantFacility, char nameFacility[][20], float priceFacility[]);
void displayFacilityBills(int QuantFacility, char nameFacility[][20], float priceFacility[], float QuantEachFacility[], float *totAllFacility); 
int initialTypeOfRoom(int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[]);
void manageFood(int *QuantFood, char nameFood[][20], float priceFood[]); 
void manageFacility(int *QuantFacility, char nameFacility[][20], float priceFacility[]); 
void updateRoomTotal(int roomType, float priceRoomDay);
void checkInRoom(int j, int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[], int *totRoom, int *dayCheckIn, float *priceRoomDay);
void checkInFood(int QuantFood, char nameFood[][20], float priceFood[], float QuantEachFood[], int roomFoodChoices[][Max_foodQuant]);
void checkInFacility(int QuantFacility, char nameFacility[][20], float priceFacility[], float QuantEachFacility[], int roomFacilityChoices[][Max_FacilityQuant]);
void checkOut(int roomAvailable[], int num_roomName, char roomName[][10], float roomPrice[], int checkOuts[], int *totRoom);

// --- MAIN FUNCTION ---
int main () {
    int mainMenu, Administrator, Reception, j, dayCheckIn;
    float grandTotal = 0, totalBillRoom = 0, priceRoomDay = 0;
    int i, num_roomName = 4, totRoom = 0;
    char roomName[][10] = {"King", "Queen", "Double", "Single"};
    int roomAvailable[4] = {0}; 
    float roomPrice[4] = {0};
    
    int QuantFood = 0;
    float priceFood[Max_foodQuant], totAllFood = 0;
    char nameFood[Max_foodQuant][20];
    float QuantEachFood[Max_foodQuant] = {0};
    int roomFoodChoices[Max_foodQuant][Max_foodQuant] = {0}; 

    int QuantFacility = 0;
    float priceFacility[Max_FacilityQuant], totAllFacility = 0;
    char nameFacility[Max_FacilityQuant][20];
    float QuantEachFacility[Max_FacilityQuant] = {0};
    int roomFacilityChoices[Max_FacilityQuant][Max_FacilityQuant] = {0}; 
    
    int checkOuts[4] = {0};
    int choosePay;
    float cash;
    char creditCardNumber[20];
    
    do {
        printf("\n+=============================================+\n");
        printf("|           HOTEL LALUNA MAIN MENU            |\n");
        printf("+---------------------------------------------+\n");
        printf("| 1. ADMINISTRATOR | 2. RECEPTION | 3. EXIT   |\n");
        printf("+=============================================+\n"); 
        printf("Enter choice: ");
        if (scanf("%d", &mainMenu) != 1) break;
        
        switch (mainMenu) {
            case 1:
                do {
                    printf("\n[ADMIN MODULE] 1.Rooms 2.Food 3.Facility 4.Back: ");
                    scanf("%d", &Administrator);
                    if (Administrator == 1) totRoom = initialTypeOfRoom(num_roomName, roomName, roomAvailable, roomPrice);
                    else if (Administrator == 2) manageFood(&QuantFood, nameFood, priceFood);
                    else if (Administrator == 3) manageFacility(&QuantFacility, nameFacility, priceFacility);
                } while (Administrator != 4);
                break;

            case 2:
                do {
                    printf("\n[RECEPTION] 1.Check-In 2.Check-Out 3.Back: ");
                    scanf("%d", &Reception);
                    if (Reception == 1) {
                        int roomCheckIn;
                        printf("Rooms to check-in: ");
                        scanf("%d", &roomCheckIn);
                        for (j = 0; j < roomCheckIn; j++) {
                            checkInRoom(j, num_roomName, roomName, roomAvailable, roomPrice, &totRoom, &dayCheckIn, &priceRoomDay);
                            displayMenuFood(QuantFood, nameFood, priceFood);
                            checkInFood(QuantFood, nameFood, priceFood, QuantEachFood, roomFoodChoices);
                            displayMenuFacility(QuantFacility, nameFacility, priceFacility);
                            checkInFacility(QuantFacility, nameFacility, priceFacility, QuantEachFacility, roomFacilityChoices);
                        }
                        totAllFood = 0; totAllFacility = 0; // Reset for receipt calculation
                        printf("\n--- RECEIPT ---\n");
                        displayFoodBills(QuantFood, nameFood, priceFood, QuantEachFood, &totAllFood);
                        displayFacilityBills(QuantFacility, nameFacility, priceFacility, QuantEachFacility, &totAllFacility);
                        grandTotal = priceRoomDay + totAllFood + totAllFacility;
                        printf("GRAND TOTAL: RM %.2f\n", grandTotal);
                    } else if (Reception == 2) {
                        checkOut(roomAvailable, num_roomName, roomName, roomPrice, checkOuts, &totRoom);
                    }
                } while (Reception != 3);
                break;
        }
    } while (mainMenu != 3);
    return 0;
}

// --- IMPLEMENTATION OF FUNCTIONS ---

int initialTypeOfRoom(int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[]) {
    int total = 0;
    for (int i = 0; i < num_roomName; i++) {
        printf("Available %s rooms: ", roomName[i]);
        scanf("%d", &roomAvailable[i]);
        printf("Price per night: RM ");
        scanf("%f", &roomPrice[i]);
        total += roomAvailable[i];
    }
    return total;
}

void displayRoomType(int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[]) {
    printf("\n%-10s %-10s %-10s\n", "Type", "Stock", "Price");
    for(int i=0; i<num_roomName; i++) printf("%-10s %-10d %-10.2f\n", roomName[i], roomAvailable[i], roomPrice[i]);
}

void manageFood(int *QuantFood, char nameFood[][20], float priceFood[]) {
    printf("How many food items to add? ");
    scanf("%d", QuantFood);
    for(int i=0; i<*QuantFood; i++) {
        printf("Food %d name: ", i+1); scanf("%s", nameFood[i]);
        printf("Price: RM "); scanf("%f", &priceFood[i]);
    }
}

void manageFacility(int *QuantFacility, char nameFacility[][20], float priceFacility[]) {
    printf("How many facilities? ");
    scanf("%d", QuantFacility);
    for(int i=0; i<*QuantFacility; i++) {
        printf("Facility %d: ", i+1); scanf("%s", nameFacility[i]);
        printf("Price: RM "); scanf("%f", &priceFacility[i]);
    }
}

void checkInRoom(int j, int num_roomName, char roomName[][10], int roomAvailable[], float roomPrice[], int *totRoom, int *dayCheckIn, float *priceRoomDay) {
    int type;
    displayRoomType(num_roomName, roomName, roomAvailable, roomPrice);
    printf("Select Room Type (1-4) for Room %d: ", j+1);
    scanf("%d", &type);
    printf("How many nights? ");
    scanf("%d", dayCheckIn);
    roomAvailable[type-1]--;
    *priceRoomDay = roomPrice[type-1] * (*dayCheckIn);
}

void displayMenuFood(int QuantFood, char nameFood[][20], float priceFood[]) {
    printf("\n--- FOOD MENU ---\n");
    for(int i=0; i<QuantFood; i++) printf("%d. %s (RM%.2f)\n", i+1, nameFood[i], priceFood[i]);
}

void checkInFood(int QuantFood, char nameFood[][20], float priceFood[], float QuantEachFood[], int roomFoodChoices[][Max_foodQuant]) {
    int choice;
    do {
        printf("Select food (1-%d, 0 to stop): ", QuantFood);
        scanf("%d", &choice);
        if(choice > 0 && choice <= QuantFood) QuantEachFood[choice-1]++;
    } while(choice != 0);
}

void displayMenuFacility(int QuantFacility, char nameFacility[][20], float priceFacility[]) {
    printf("\n--- FACILITIES ---\n");
    for(int i=0; i<QuantFacility; i++) printf("%d. %s (RM%.2f)\n", i+1, nameFacility[i], priceFacility[i]);
}

void checkInFacility(int QuantFacility, char nameFacility[][20], float priceFacility[], float QuantEachFacility[], int roomFacilityChoices[][Max_FacilityQuant]) {
    int choice;
    do {
        printf("Select facility (1-%d, 0 to stop): ", QuantFacility);
        scanf("%d", &choice);
        if(choice > 0 && choice <= QuantFacility) QuantEachFacility[choice-1]++;
    } while(choice != 0);
}

void displayFoodBills(int QuantFood, char nameFood[][20], float priceFood[], float QuantEachFood[], float *totAllFood) {
    for(int i=0; i<QuantFood; i++) {
        if(QuantEachFood[i] > 0) {
            printf("%s x%.0f: RM%.2f\n", nameFood[i], QuantEachFood[i], QuantEachFood[i]*priceFood[i]);
            *totAllFood += QuantEachFood[i]*priceFood[i];
        }
    }
}

void displayFacilityBills(int QuantFacility, char nameFacility[][20], float priceFacility[], float QuantEachFacility[], float *totAllFacility) {
    for(int i=0; i<QuantFacility; i++) {
        if(QuantEachFacility[i] > 0) {
            printf("%s x%.0f: RM%.2f\n", nameFacility[i], QuantEachFacility[i], QuantEachFacility[i]*priceFacility[i]);
            *totAllFacility += QuantEachFacility[i]*priceFacility[i];
        }
    }
}

void checkOut(int roomAvailable[], int num_roomName, char roomName[][10], float roomPrice[], int checkOuts[], int *totRoom) {
    int type;
    printf("Check-out room type (1-4): ");
    scanf("%d", &type);
    if(type >= 1 && type <= 4) {
        roomAvailable[type-1]++;
        (*totRoom)++;
        printf("Room %s is now vacant.\n", roomName[type-1]);
    }
}