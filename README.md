# portfolio-project

To obtain the data file to use this IMDB database program:
1. Use this link to download the IMDB "basics" data file. https://datasets.imdbws.com/title.basics.tsv.gz
2. Extract the file to a folder called title.basics.tsv.
3. Use the following command to obtain a file containing just movies:
    grep "movie" title.basics.tsv > movie_records
4. At this point, you can make the executable and run the program.
