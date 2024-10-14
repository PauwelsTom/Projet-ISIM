Projet ISIM

Samuel Michaud
Tom Pauwels


1. Run le projet

Il suffit de faire un make dans le root du projet ("/projet-isim/")



2. Utiliser le projet

Pour creer votre scene il vous suffit d'aller dans "./raymarcher.cpp" et d'ajouter vous objets et vos lumières


3. Prochains trucs a faire 

    - Faire des textures suplementaire

    - Faire en sorte que les textures prennent en compte la lumiere

    - Material Réfléchissant


4. Problemes

    - Quand on bouge les spheres, des fois ya des bouts qui disparaissent (en mode y'a de l'ombre).
        -> Partiellement regle avec size dans "isInShadow".
            Fonction a reprendre pour regler ce probleme.
    
    - Avec le plan du fond (voir "./screen_projet/Probleme_cercles_plan_fond.ppm"), 
      on voit apparaitre des cercles autour des boules.

        -> Creation de la douille du siecle (voir 'size2' dans "isInShadow").
            Toujours cette fonction a retoucher.