#include <iostream>
#include <list>
#include <string>

int main() {

  std::list<std::list<std::string>> wordsOneMeaning = {{"enough", "tarpeeksi"},
                                            //Adjectives
                                             {"good"}, {"hyvä"},
                                             //Numbers
                                             {"one", "yksi"},
                                             {"two", "kaksi"},
                                             {"three","kolme"}
                                             ,{"four","neljä"}
                                             ,{"five","viisi"}
                                             ,{"six","kuusi"}
                                             ,{"seven","seitsemän"}
                                             ,{"eight","kahdeksan"}
                                             ,{"nine","yhdeksän"}
                                             ,{"ten","kymmenen"}
                                             ,{"eleven","yksikoista"}
                                             ,{"twelve","kaksitoista"}
                                             //Verbs
                                             ,{"to be","ole"}
                                             ,{"to eat","syödä"}
                                             ,{"to drink","juoda"}
                                             ,{"to run","juoksee"}
                                             ,{"to love","rakastaa"}
                                             //Geography
                                             ,{"Finland","Suomi"}
                                             ,{"Sweden","Ruotsi"}
                                             //Pronouns
                                             ,{"I","minä"}
                                             ,{"you","sinä"}
                                             ,{"he / she","hän"}
                                             ,{"we","me"}
                                             ,{"you","te"}
                                             ,{"they","he"}
                                             ,{"they","he"}
                                             //Words
                                             ,{"man","mies"}
                                             ,{"woman","nainen"}
                                             //Other
                                             ,{"and","ja"}
                                             };

    std::list<std::list<std::string>> wordsTwoMeaning = {
                                             //Adjectives
                                             ,{"nice","mukava"}
                                             //Numbers
                                             //Verbs
                                             //Pronouns
                                             ,{"he / she","hän"}
                                             //Words
                                             //Other
                                             };

  return 0;
}
