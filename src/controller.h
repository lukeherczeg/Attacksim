#ifndef CONTROLLER_H_
#define CONTROLLER_H_

class Controller{
private:
	int damage, numTimes, totalHP, programLoops, attackDamage, criticalDamage, percentCrit, percentHeal;
	const int modifier = 1, heal = 10;
	bool attacking, attacked, ready, program, isCritical;
	std::string input;
public:
	Controller();
	void attackSequence();
	void damageInit();
	void run();
	void scene(int programLoops);
};



#endif /* CONTROLLER_H_ */
