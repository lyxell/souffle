/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2020 The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file TranslatorContext.h
 *
 ***********************************************************************/

#pragma once

#include "souffle/utility/ContainerUtil.h"
#include <cstddef>
#include <set>

namespace souffle::ast {
class Clause;
class QualifiedName;
class Relation;
class SipsMetric;
class TranslationUnit;
}  // namespace souffle::ast

namespace souffle::ast::analysis {
class RecursiveClausesAnalysis;
class RelationDetailCacheAnalysis;
class RelationScheduleAnalysis;
class SCCGraphAnalysis;
}  // namespace souffle::ast::analysis

namespace souffle::ast2ram {

class TranslatorContext {
public:
    TranslatorContext(ast::TranslationUnit& tu);

    /** Relation methods */
    ast::Relation* getRelation(const ast::QualifiedName& name) const;

    /** Clause methods */
    std::set<ast::Clause*> getClauses(const ast::QualifiedName& name) const;
    bool isRecursiveClause(const ast::Clause* clause) const;

    /** SCC methods */
    size_t getNumberOfSCCs() const;
    bool isRecursiveSCC(size_t scc) const;
    std::set<const ast::Relation*> getExpiredRelations(size_t scc) const;
    std::set<const ast::Relation*> getRelationsInSCC(size_t scc) const;
    std::set<const ast::Relation*> getInputRelationsInSCC(size_t scc) const;
    std::set<const ast::Relation*> getOutputRelationsInSCC(size_t scc) const;

    /** Analyses */
    const ast::SipsMetric* getSipsMetric() const {
        return sipsMetric.get();
    }

private:
    const ast::analysis::RecursiveClausesAnalysis* recursiveClauses;
    const ast::analysis::RelationScheduleAnalysis* relationSchedule;
    const ast::analysis::SCCGraphAnalysis* sccGraph;
    const ast::analysis::RelationDetailCacheAnalysis* relationDetail;
    Own<ast::SipsMetric> sipsMetric;
};

}  // namespace souffle::ast2ram
