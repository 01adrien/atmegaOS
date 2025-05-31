#if !defined(_INTERRUPT_H_)
#define _INTERRUPT_H_

/*
Les vecteurs d’interruptions se trouvent en mémoire Flash à partir de l’adresse 0x0000,
car ils font partie du code programme. En revanche, les registres d'I/O commencent à
0x20 dans l’espace mémoire des données (SRAM/I/O).
Il n’y a donc pas de conflit :
ces deux zones d’adresses appartiennent à des espaces mémoire différents.

__attribute__((signal)) :
- Indique que la fonction est une ISR (handler d’interruption).
- Génère un prologue/épilogue adapté (sauvegarde/restauration des registres).
- Utilise l’instruction 'reti' pour retourner de l’interruption.

__attribute__((used)) :
- Empêche la suppression de la fonction par le compilateur même si elle semble inutilisée.
- Utile pour les ISR référencées uniquement via la table des vecteurs.

Active ou désactive les interruptions globales.

Ces fonctions encapsulent les instructions assembleur `sei` (Set Interrupt Flag)
et `cli` (Clear Interrupt Flag) qui modifient directement le bit I (Interrupt Enable)
du registre de statut (SREG).

On utilise de l’assembleur inline car il n'existe pas d'équivalent C standard
pour activer/désactiver les interruptions au niveau machine.
*/

static inline void interrupt_enable(void)
{
    __asm__ __volatile__("sei" ::: "memory");
}

static inline void interrupt_disable(void)
{
    __asm__ __volatile__("cli" ::: "memory");
}

void __vector_1(void) __attribute__((signal, used));
void __vector_2(void) __attribute__((signal, used));
void __vector_3(void) __attribute__((signal, used));
void __vector_4(void) __attribute__((signal, used));
void __vector_5(void) __attribute__((signal, used));
void __vector_6(void) __attribute__((signal, used));
void __vector_7(void) __attribute__((signal, used));
void __vector_8(void) __attribute__((signal, used));
void __vector_9(void) __attribute__((signal, used));
void __vector_10(void) __attribute__((signal, used));
void __vector_11(void) __attribute__((signal, used));
void __vector_12(void) __attribute__((signal, used));
void __vector_13(void) __attribute__((signal, used));
void __vector_14(void) __attribute__((signal, used));
void __vector_15(void) __attribute__((signal, used));
void __vector_16(void) __attribute__((signal, used));
void __vector_17(void) __attribute__((signal, used));
void __vector_18(void) __attribute__((signal, used));
void __vector_19(void) __attribute__((signal, used));
void __vector_20(void) __attribute__((signal, used));
void __vector_21(void) __attribute__((signal, used));
void __vector_22(void) __attribute__((signal, used));
void __vector_23(void) __attribute__((signal, used));
void __vector_24(void) __attribute__((signal, used));
void __vector_25(void) __attribute__((signal, used));
void __vector_26(void) __attribute__((signal, used));
void __vector_27(void) __attribute__((signal, used));
void __vector_28(void) __attribute__((signal, used));
void __vector_29(void) __attribute__((signal, used));

#endif // _INTERRUPT_H_
