library(dplyr)

# Wczytuję ramki Posts i Users z odpowiedniej bazy danych. W ten sposób mogę
# napisać jeden kod do wszystkich baz danych i podmieniać jedynie ścieżki lub
# pliki znajdujące się pod daną ścieżką.
Posts <- read.csv("../data/Posts-Bioinformatics.csv")
Users <- read.csv("../data/Users-Bioinformatics.csv")

  
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

write.csv(PostsUseful,"../data/wyniki/Edges.csv",
          row.names = FALSE)
write.csv(UsersUseful,"../data/wyniki/Vertices.csv",
          row.names = FALSE)
?write.csv
