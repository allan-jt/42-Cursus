#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() {}
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};

class MateriaSource : public IMateriaSource {
	private:
		AMateria *_materia[4];
	
	public:
		void		learnMateria(AMateria*);
		AMateria	*createMateria(std::string const & type);
		
		// (con/de)structors
		MateriaSource(void);
		MateriaSource(std::string const &name);
		MateriaSource(MateriaSource const &copy);
		virtual ~MateriaSource(void);
		MateriaSource &operator=(MateriaSource const &rhs);
};

#endif