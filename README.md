The Movie Multiplex Scheduler is a tool coded in C programming language to generate a weekly schedule for a given multiplex such that the profit for 
the multiplex is maximized.

The initial input parameters involve the number of screens in the multiplex that uses the Scheduler and its capacity. Following this, the number of 
movies to be screened for that week is taken as input.

For each movie,the release date,movie rating and language is taken from the users to calculate the demand and popularity scores of the movies respectively.

The movies are sorted based on the above-mentioned parameters. Screens are allotted per movie based on the combined demand and popularity score. 
Calculations are made to generate an occupancy matrix with the percentage of audience predicted to fill the capacity in that particular slot in a 
given screen and a binary matrix is generated to indicate whether the movie is being assigned to that slot or not. 
The schedule for a week is generated and crowd management is incorporated by adding appropriate time gaps for each consecutive slot and screen. 

The generated schedule for a week is stored in a file "movie_schedule.txt" which is opened in append mode each time the program is run.


## Test Cases
Number of movies < Number of Screens

1. Number of screens: 8

   Number of movies: 3

Movie 1

    Release Date : 26/08/2022
    Rating : 9
    Language : 1-Tamil

Movie 2

    Release Date : 15/08/2022
    Rating : 5
    Language : 2-English

Movie 3

    Release Date : 15/08/2022
    Rating : 7
    Language : 3-Other regional languages

2. Number of screens : 14

   Number of movies : 6

Movie 1

    Release Date : 26/08/2022
    Rating : 8
    Language : 1-Tamil

Movie 2

    Release Date : 16/08/2022
    Rating : 5
    Language : 3-Other regional languages

Movie 3 
     
    Release Date : 13/08/2022
    Rating : 7
    Language : 1-Tamil

Movie 4

    Release Date : 08/08/2022
    Rating : 9
    Language : 2-English

Movie 5
    Release Date : 16/08/2022
    Rating : 8
    Language : 1-Tamil

Movie 6
    Release Date : 07/08/2022
    Rating : 2
    Language : 2-English

Number of movies = Number of Screens

3. Number of screens : 2

   Number of movies : 2

Movie 1

    Release Date : 26/08/2022
    Rating : 10
    Language : 1-Tamil

Movie 2

    Release Date : 23/08/2022
    Rating : 9
    Language : 2-English

Number of movies > Number of Screens

4. Number of screens: 2 

   Number of movies: 3

Movie 1

    Release Date : 09/08/2022
    Rating : 8
    Language : 1-Tamil

Movie 2

    Release Date : 15/08/2022
    Rating : 8
    Language : 2-English

Movie 3

    Release Date : 26/08/2022
    Rating : 9
    Language : 1-Tamil
