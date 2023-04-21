#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_MOVIES 5
#define MAX_SEATS 100

struct movie 
{
    char name[50];
    int id;
    char genre[20];
    int rating;
    int duration;
};

struct booking 
{
    char name[50];
    int movie_id;
    int seat_no;
    int payment_amt;
};

struct movie movies[MAX_MOVIES];
struct booking bookings[MAX_SEATS];
int num_movies = 0;
int num_bookings = 0;

void display_movies();
void register_movie();
void book_ticket();
void cancel_ticket();
void view_bookings();

int main() 
{
    int choice;
    do 
    {
        printf("\n\nMovie Ticket Booking System\n");
        printf("1. Display movies\n");
        printf("2. Register movie\n");
        printf("3. Book ticket\n");
        printf("4. Cancel ticket\n");
        printf("5. View bookings\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) 
        {
            case 1:
                display_movies();
                break;
            case 2:
                register_movie();
                break;
            case 3:
                book_ticket();
                break;
            case 4:
                cancel_ticket();
                break;
            case 5:
                view_bookings();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);
    return 0;
}

void display_movies() 
{
    if (num_movies == 0) 
    {
        printf("No movies registered.\n");
        return;
    }
    printf("\nMovies currently showing:\n");
    for (int i = 0; i < num_movies; i++) 
    {
        printf("%d. %s (%s, %d minutes, rating: %d/10)\n", movies[i].id, 
        movies[i].name,movies[i].genre,movies[i].duration, movies[i].rating);
    }
}

void register_movie() 
{
    if (num_movies == MAX_MOVIES)
    {
        printf("Maximum number of movies reached.\n");
        return;
    }
    printf("\nEnter movie details:\n");
    printf("Name: ");
    scanf("%s", movies[num_movies].name);
    printf("Genre: ");
    scanf("%s", movies[num_movies].genre);
    printf("Duration (in minutes): ");
    scanf("%d", &movies[num_movies].duration);
    printf("Rating (out of 10): ");
    scanf("%d", &movies[num_movies].rating);
    movies[num_movies].id = num_movies + 1;
    num_movies++;
    printf("Movie registered successfully.\n");
}

void book_ticket() 
{
    if (num_movies == 0) 
    {
        printf("No movies registered.\n");
        return;
    }
    int movie_id, num_seats, payment_amt;
    printf("\nEnter movie ID: ");
    scanf("%d", &movie_id);
    if (movie_id < 1 || movie_id > num_movies) 
    {
        printf("Invalid movie ID.\n");
        return;
    }
    printf("Enter number of seats: ");
    scanf("%d", &num_seats);
    if (num_seats <= 0 || num_seats > MAX_SEATS) 
    {
        printf("Invalid number of seats.\n");
        return;
    }
    printf("Enter payment amount: ");
    scanf("%d", &payment_amt);
    if (payment_amt <= 0) 
    {
        printf("Invalid payment amount.\n");
        return;
    }
    int available_seats = MAX_SEATS - num_bookings;
    if (num_seats > available_seats) 
    {
        printf("Not enough seats available.\n");
        return;
    }
    printf("\nEnter customer name: ");
    scanf("%s", bookings[num_bookings].name);
    bookings[num_bookings].movie_id = movie_id;
    bookings[num_bookings].payment_amt = payment_amt;
    printf("Seat numbers:");
    for (int i = 0; i < num_seats; i++) 
    {
        bookings[num_bookings].seat_no = num_bookings + 1;
        printf(" %d", num_bookings + 1);
        num_bookings++;
    }
    printf("\nBooking confirmed. Payment of %d received.\n", payment_amt);
}

void cancel_ticket() 
{
    if (num_bookings == 0) 
    {
        printf("No bookings made.\n");
        return;
    }
    int booking_id;
    printf("\nEnter booking ID to cancel: ");
    scanf("%d", &booking_id);
    if (booking_id < 1 || booking_id > num_bookings) 
    {
        printf("Invalid booking ID.\n");
        return;
    }
    booking_id--;
    int movie_id = bookings[booking_id].movie_id;
    int num_seats = 0;
    for (int i = booking_id; i < num_bookings - 1; i++) 
    {
        bookings[i] = bookings[i + 1];
        if (bookings[i].movie_id == movie_id) 
        num_seats++;
    }
    num_bookings--;
    printf("\nBooking cancelled. Refund of %d initiated.\n", 
           bookings[booking_id].payment_amt);
    if (num_seats > 0) 
    printf("%d seats now available for movie ID %d.\n", num_seats,movie_id);
}

void view_bookings() 
{
    if (num_bookings == 0) 
    {
        printf("No bookings made.\n");
        return;
    }
    printf("\nAll bookings:\n");
    for (int i = 0; i < num_bookings; i++) 
    printf("%d. %s (Movie ID: %d, Seat No: %d, Payment Amt: %d)\n", i + 1, 
           bookings[i].name, bookings[i].movie_id, bookings[i].seat_no, 
           bookings[i].payment_amt);
}
