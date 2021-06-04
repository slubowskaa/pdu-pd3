library(XML)
library(dplyr)

xml2csv <- function(input,output){
  xmlParse(input) %>% getNodeSet(path = "//row") %>%
  XML:::xmlAttrsToDataFrame() %>% write.csv(output)
}

xml2csv("E:/RStudio/Trzeci projekt/bazy danych/gaming/Posts.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Posts-Gaming.csv")
xml2csv("E:/RStudio/Trzeci projekt/bazy danych/gaming/Users.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Users-Gaming.csv")

xml2csv("E:/RStudio/Trzeci projekt/bazy danych/chess/Posts.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Posts-Chess.csv")
xml2csv("E:/RStudio/Trzeci projekt/bazy danych/chess/Users.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Users-Chess.csv")

xml2csv("E:/RStudio/Trzeci projekt/bazy danych/bioinformatics/Posts.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Posts-Bioinformatics.csv")
xml2csv("E:/RStudio/Trzeci projekt/bazy danych/bioinformatics/Users.xml",
        "E:/RStudio/Trzeci projekt/bazy danych/Users-Bioinformatics.csv")
