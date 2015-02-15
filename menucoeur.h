#ifndef MENU_COEUR_H__
#define MENU_COEUR_H__

#include "menu.h"

class MenuCoeur : public Menu {
public:
	static MenuCoeur* GetInstance();
	static MenuCoeur* Instanciate(int windowX, int windowY);

	virtual void Center(int windowX, int windowY);
	virtual void InitButtons();

	virtual int GetNbCoeur();
	virtual void SetNbCoeur(int nbcoeur);

	virtual void Show() { }
	virtual void Hide() { }
	virtual bool IsShowed() { return true; }

protected:
	MenuCoeur(int windowX, int windowY);
	static MenuCoeur* m_instance;
	int m_nbcoeur;
};

#endif