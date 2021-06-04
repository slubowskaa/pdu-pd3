library(XML)
library(dplyr)

xml2csv <- function(input,output){
  xmlParse(input) %>% getNodeSet(path = "//row") %>%
  XML:::xmlAttrsToDataFrame() %>% write.csv(output)
}

xml2csv("../data/gaming/Posts.xml",
        "../data/Posts-Gaming.csv")
xml2csv("../data/gaming/Users.xml",
        "../data/Users-Gaming.csv")

xml2csv("../data/chess/Posts.xml",
        "../data/Posts-Chess.csv")
xml2csv("../data/chess/Users.xml",
        "../data/Users-Chess.csv")

xml2csv("../data/bioinformatics/Posts.xml",
        "../data/Posts-Bioinformatics.csv")
xml2csv("../data/bioinformatics/Users.xml",
        "../data/Users-Bioinformatics.csv")
