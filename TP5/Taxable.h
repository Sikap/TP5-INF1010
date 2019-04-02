//
//  Taxable.h
//
//  Created by Martine Bellaiche on 2019-03-05.
//  Copyright © 2019 Martine Bellaiche. All rights reserved.
//

#ifndef TAXABLE_H
#define TAXABLE_H
class Taxable
{
public:
	virtual void setTaxe() = 0;
	virtual double getTaxe() const = 0;
};

#endif /* Taxable_h */
