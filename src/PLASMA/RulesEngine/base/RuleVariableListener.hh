#ifndef H_RuleVariableListener
#define H_RuleVariableListener

#include "RulesEngineDefs.hh"
#include "Constraint.hh"

namespace EUROPA
{
  /**
   * @brief Responsible for integrating Rule Guard Variables to the propagation network, so that
   * rule evaluation can be triggered when relevant rule variables change.
   *
   * This class is a connector class between the rules engine and the constraint engine.
   * @see RuleInstance 
   */
  class RuleVariableListener: public Constraint
  {
  public:
    /**
     * @brief Standard constraint constructor must be provided to facilitate
     * creation of a copy during merging.
     */
    RuleVariableListener(const std::string& name,
			 const std::string& propagatorName,
			 const ConstraintEngineId constraintEngine, 
			 const std::vector<ConstrainedVariableId>& variables);

    /**
     * @brief Implement this method to allow ruleInstance data to be extracted and copied
     */
    void setSource(const ConstraintId sourceConstraint);

    const RuleInstanceId getRuleInstance();

    /**
     * @brief Standard constraint name
     */
    static const std::string& CONSTRAINT_NAME(){
      static const std::string sl_const("RuleVariableListener");
      return sl_const;
    }

    /**
     * @brief Standard propagator
     */
    static const std::string& PROPAGATOR_NAME(){
      static const std::string sl_const("RulesEngine");
      return sl_const;
    }

  private:

    /**
     * @brief Handles messages from a rule instance when discarded to trigger a deactivation
     */
    virtual void notifyDiscarded(const Entity* entity);

    /**
     * @brief Handle rule related deallocations
     */
    virtual void handleDiscard();

    /**
     * @brief Over-ride base class test
     */
    virtual bool testIsRedundant(const ConstrainedVariableId var = ConstrainedVariableId::noId()) const;

    friend class RuleInstance;

    /**
     * @brief Constructor used internally by the RuleInstance class when allocating
     * the listener.
     */
    RuleVariableListener(const ConstraintEngineId constraintEngine,
			 const RuleInstanceId ruleInstance,
			 const std::vector<ConstrainedVariableId>& scope);

    bool canIgnore(const ConstrainedVariableId variable, 
		   unsigned int argIndex, 
		   const DomainListener::ChangeType& changeType);

    void handleExecute();
    void handleExecute(const ConstrainedVariableId variable,
		       unsigned int argIndex,
		       const DomainListener::ChangeType& changeType) {Constraint::handleExecute(variable, argIndex, changeType);}

    RuleInstanceId m_ruleInstance;
    ConstraintId m_sourceConstraint;
  };
}
#endif
