library(dplyr)
library(here)



getUsefulPostsData <- function(input,output){
  read.csv(input) %>% select(OwnerUserId,PostTypeId) %>%
  filter(PostTypeId == 1 | PostTypeId == 2) %>% filter(!is.na(OwnerUserId)) %>%
  write.csv(output,row.names = FALSE)
}

forum_names <- c(
  "gaming",
  "chess",
  "bioinformatics",
  "health", 
  "beer", 
  "bicycles", 
  "coffee", 
  "fitness", 
  "lifehacks", 
  "music", 
  "photo", 
  "travel",
  "vegetarianism", 
  "pets", 
  "parenting", 
  "cooking", 
  "bitcoin", 
  "astronomy", 
  "literature", 
  "sports"
)




for (forum_name in forum_names) {
  
  getUsefulPostsData(here("data", paste("Posts-", forum_name, ".csv", sep="")),
                     here("data", "wyniki", paste("PostsForCounting-", forum_name, ".csv", sep="")))
}

