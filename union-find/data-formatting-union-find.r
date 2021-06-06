library(dplyr)
library(here)
 

forum_names <-  c("vegetarianism", "pets", "parenting", "cooking", "bitcoin", "astronomy", "literature", "sports")

for (f_name in forum_names) {
  Posts <- read.csv(here("data", paste("Posts-", f_name, ".csv", sep="")))
  Users <- read.csv(here("data", paste("Users-", f_name, ".csv", sep="")))
  
  
  # Biorę tylko dane potrzebne do algorytmu. Bazy danych są duże i jest potrzeba
  # oszczędzania pamięci.
  PostsUseful <- (
    filter(Posts,PostTypeId == 2) %>% select(OwnerUserId,Id,ParentId) %>%
      rename(AnsUserId = OwnerUserId,AnsId = Id,Id = ParentId) %>%
      inner_join(Posts,by = "Id") %>% 
      select(AnsUserId,OwnerUserId) %>% rename(QuesUserId = OwnerUserId) %>%
      # Pozbywam się zepsutych obserwacji.
      filter(!is.na(AnsUserId) & !is.na(QuesUserId))
  )
  
  UsersUseful <- (
    select(Users,Id) %>% filter(Id > 0)
  )
  
  # Zapisuję z powrotem do pliku, w formacie .csv ,ponieważ z nim potrafię
  # pracować w innych, szybszych językach programowania. Find & Union jest 
  # szybkie, ale w R i tak bym czekał wieki aż się wykona, więc zdecydowałem, że
  # rozdzielę projekt między kilka różnych języków programowania.
  
  write.csv(PostsUseful, here("data", "wyniki", paste("Edges-", f_name, ".csv", sep="")),
            row.names = FALSE)
  write.csv(UsersUseful, here("data", "wyniki", paste("Vertices-", f_name, ".csv", sep="")),
            row.names = FALSE)
}
