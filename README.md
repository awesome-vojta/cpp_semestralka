# cpp_semestralka
semestralni prace na predmet zaklady cpp, ucitel: Konopa

// Pozadavek na smysluplnou demonstraci: Work >> PrivateWork & CompanyWork
// Private: vyzaduje jednoho pracovnika
// Company: vyzaduje vice pracovniku


Požadovaná funkcionalita:
-------------------------
1. Přidání a odebrání konkrétní nabízené činnosti.
   Změna hodinové taxy existující činnosti (v aktuální nabídce firmy).
        ->type: "pw" / "cw" to add
        ->type: "delete" to delete

2. Přidání a odebrání konkrétního zaměstance firmy.
        ->type: "w" to add
        ->type: "delete" to delete

3. Přidání záznamu o vykonané zakázce:
   - činnost, která se prováděla
   - kolik hodin to trvalo
   - seznam zaměstnanců, kteří se na činnosti podíleli
   - kdy byla zakázka realizována
     (pro jednoduchost pořadový den v roce: 1..365)
        ->type: "pw" / "cw" to add

4. Historické přehledy (za určité období v roce):
   - kolik firma celkově utržila
   - jaký zaměstnanec vykonal které činnosti a kolik celkově "stál" zákazníky
     peněz
   - činnost, která byla prováděna nejčastěji a nejméné často (nejnižší zájem)
   - zaměstnanec, který stál zákazníky nejvíce peněz
   - zaměstnanec, který pracoval na nejvíce zakázkách
           ->type: "profit" to show grossProfit

   VČETNĚ zaměstnanců, kteří u firmy již nepracují, a činností, které již
   firma v reperotáru nemá.

5. Program nabídne uživateli i možnost uložení historie do souboru a její
   možné načtení ze souboru do programu.
           ->type: "save"
           ->type: "load"
