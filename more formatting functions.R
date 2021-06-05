library(dplyr)

getUsefulPostsData <- function(input,output){
  read.csv(input) %>% select(OwnerUserId,PostTypeId) %>%
  filter(PostTypeId == 1 | PostTypeId == 2) %>% filter(!is.na(OwnerUserId)) %>%
  write.csv(output,row.names = FALSE)
}

getUsefulPostsData("E:/RStudio/Trzeci projekt/bazy danych/Posts-AI.csv",
                   "E:/RStudio/Trzeci projekt/wyniki/PostsForCounting.csv")
