library(XML)
library(dplyr)
library(here)


xml2csv <- function(input,output){
  xmlParse(input) %>% getNodeSet(path = "//row") %>%
  XML:::xmlAttrsToDataFrame() %>% write.csv(output)
}

forum_names <- c("vegetarianism", "pets", "parenting", "cooking", "bitcoin", "astronomy", "literature", "sports")

for (forum_name in forum_names) {
  xml2csv(here("data", forum_name, "Posts.xml"),
          here("data", paste("Posts-", forum_name, ".csv", sep="")))
  xml2csv(here("data", forum_name, "Users.xml"),
          here("data", paste("Users-", forum_name, ".csv", sep="")))
}
