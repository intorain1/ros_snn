#include "model.h"
#include "add_model.cc"
//------------------------------------------------------------------------------
// POISON model P
//------------------------------------------------------------------------------
// policy_net
double ini_Poi1[] = {
    Poi_V1,
    Poi_seed1,
    Poi_trace1,
};
double p_Poi1[] = {
    Poi_Vspike1,
    Poi_Vrest1,
    Poi_Ttrace1,
};
// target_net
double ini_Poi2[] = {
    Poi_V2,
    Poi_seed2,
    Poi_trace2,
};
double p_Poi2[] = {
    Poi_Vspike2,
    Poi_Vrest2,
    Poi_Ttrace2,
};

//------------------------------------------------------------------------------
// LIF model E&I
//------------------------------------------------------------------------------
// policy_net
double ini_Exc1[] = {
    Exc_V1,
    Exc_theta1,
    Exc_timer1,
    Exc_trace1,
    Exc_trace2,
    Exc_trace,
    Exc_testDataEvaluateMode1,
};
double p_Exc1[] = {
    Exc_TV1,
    Exc_Vrest1,
    Exc_Vreset1,
    Exc_Vthresh1,
    Exc_Refrac1,
    Exc_test_mode1,
    Exc_Ttheta1,
    Exc_theta_plus1,
    Exc_offset1,
    Exc_Ttrace1,
    Exc_Ttrace2,
    Exc_Ttrace,
};
double ini_Inh1[] = {
    Inh_V1,
    Inh_timer1,
};
double p_Inh1[] = {
    Inh_TV1,
    Inh_Vrest1,
    Inh_Vreset1,
    Inh_Vthresh1,
    Inh_Refrac1,
};
// target_net
double ini_Exc2[] = {
    Exc_V2,
    Exc_theta2,
    Exc_timer2,
    Exc_trace1,
    Exc_trace2,
    Exc_trace,
    Exc_testDataEvaluateMode2,
};
double p_Exc2[] = {
    Exc_TV2,
    Exc_Vrest2,
    Exc_Vreset2,
    Exc_Vthresh2,
    Exc_Refrac2,
    Exc_test_mode2,
    Exc_Ttheta2,
    Exc_theta_plus2,
    Exc_offset2,
    Exc_Ttrace1,
    Exc_Ttrace2,
    Exc_Ttrace,
};
double ini_Inh2[] = {
    Inh_V2,
    Inh_timer2,
};
double p_Inh2[] = {
    Inh_TV2,
    Inh_Vrest2,
    Inh_Vreset2,
    Inh_Vthresh2,
    Inh_Refrac2,
};
// policy_net
double ini_Cla1[] = {
    Cla_V1,
    Cla_seed1,
    Cla_trace1,
    Cla_trace2,
    Cla_testDataEvaluateMode1,
};
double p_Cla1[] = {
    Cla_TV1,
    Cla_Vrest1,
    Cla_Vreset1,
    Cla_Vthresh1,
    Cla_Vspike1,
    Cla_Ttrace1,
    Cla_Ttrace2,
    Cla_test_mode1,
};
// target_net
double ini_Cla2[] = {
    Cla_V2,
    Cla_seed2,
    Cla_trace1,
    Cla_trace2,
    Cla_testDataEvaluateMode2,
};
double p_Cla2[] = {
    Cla_TV2,
    Cla_Vrest2,
    Cla_Vreset2,
    Cla_Vthresh2,
    Cla_Vspike2,
    Cla_Ttrace1,
    Cla_Ttrace2,
    Cla_test_mode2,
};
//------------------------------------------------------------------------------
// postSynV
//------------------------------------------------------------------------------
// policy_net
double postExpP2E1[2] = {
    P2E_tau_S, // decay time constant for S [ms]
    P2E_Erev,  // Reversal potential
};
double postExpE2I1[2] = {
    E2I_tau_S,
    E2I_Erev,
};
double postExpI2E1[2] = {
    I2E_tau_S,
    I2E_Erev,
};
double *postSynV1 = NULL;
// target_net
double postExpP2E2[2] = {
    P2E_tau_S, // decay time constant for S [ms]
    P2E_Erev,  // Reversal potential
};
double postExpE2I2[2] = {
    E2I_tau_S,
    E2I_Erev,
};
double postExpI2E2[2] = {
    I2E_tau_S,
    I2E_Erev,
};
double *postSynV2 = NULL;
//------------------------------------------------------------------------------
// DA_STDP
//------------------------------------------------------------------------------
// policy_net
double ini_DA_STDP_PE1[] = {
    da_stdp_PE_g,
    da_stdp_PE_testDataEvaluateMode1,
};
double p_DA_STDP_PE1[] = {
    da_stdp_PE_nu_ee_pre,
    da_stdp_PE_nu_ee_post,
    da_stdp_PE_g_min,
    da_stdp_PE_g_max,
    da_stdp_PE_a_plus,
    da_stdp_PE_a_minus,
};
double ini_DA_STDP_EC1[] = {
    da_stdp_EC_g,
    da_stdp_EC_testDataEvaluateMode1,
};
double p_DA_STDP_EC1[] = {
    da_stdp_EC_nu_ee_pre,
    da_stdp_EC_nu_ee_post,
    da_stdp_EC_g_min,
    da_stdp_EC_g_max,
    da_stdp_EC_a_plus,
    da_stdp_EC_a_minus,
};
// target_net
double ini_DA_STDP_PE2[] = {
    da_stdp_PE_g,
    da_stdp_PE_testDataEvaluateMode2,
};
double p_DA_STDP_PE2[] = {
    da_stdp_PE_nu_ee_pre,
    da_stdp_PE_nu_ee_post,
    da_stdp_PE_g_min,
    da_stdp_PE_g_max,
    da_stdp_PE_a_plus,
    da_stdp_PE_a_minus,
};
double ini_DA_STDP_EC2[] = {
    da_stdp_EC_g,
    da_stdp_EC_testDataEvaluateMode2,
};
double p_DA_STDP_EC2[] = {
    da_stdp_EC_nu_ee_pre,
    da_stdp_EC_nu_ee_post,
    da_stdp_EC_g_min,
    da_stdp_EC_g_max,
    da_stdp_EC_a_plus,
    da_stdp_EC_a_minus,
};
//------------------------------------------------------------------------------
// noSTDP
//------------------------------------------------------------------------------
// policy_net
double ini_noSTDP1[] = {
    no_stdp_g,
};
double *p_noSTDP_PE1 = NULL;
double *p_noSTDP_EC1 = NULL;
// target_net
double ini_noSTDP2[] = {
    no_stdp_g,
};
double *p_noSTDP_PE2 = NULL;
double *p_noSTDP_EC2 = NULL;
//------------------------------------------------------------------------------
// E——>I & I——>E
//------------------------------------------------------------------------------
// policy_net
double ini_NSYNAPSE_EI1[] = {
    g_EI,
};
double *p_NSYNAPSE_EI1 = NULL;
double ini_NSYNAPSE_IE1[] = {
    g_IE,
};
double *p_NSYNAPSE_IE1 = NULL;
// target_net 
double ini_NSYNAPSE_EI2[] = {
    g_EI,
};
double *p_NSYNAPSE_EI2 = NULL;
double ini_NSYNAPSE_IE2[] = {
    g_IE,
};
double *p_NSYNAPSE_IE2 = NULL;


size_t size_gP2E = NPoi * NExc;
size_t size_gE2C = NExc * NCla;

void modelDefinition(NNmodel &model)
{
    initGeNN();

#ifdef DEBUG
    GENN_PREFERENCES::debugCode = true;
#else
    GENN_PREFERENCES::optimizeCode = true;
#endif
    GENN_PREFERENCES::autoRefractory = 0;

    // policy_net
    int Poi1 = addNeuronModel_Poi(nModels);
    int LIF_Exc1 = addNeuronModel_LIF_Exc(nModels);
    int LIF_Inh1 = addNeuronModel_LIF_Inh(nModels);
    int LIF_Cla1 = addNeuronModel_LIF_Cla(nModels);
    int DA_STDP1 = addSynapseModel_DA_STDP(weightUpdateModels);

    // target_net
    int Poi2 = addNeuronModel_Poi(nModels);
    int LIF_Exc2 = addNeuronModel_LIF_Exc(nModels);
    int LIF_Inh2 = addNeuronModel_LIF_Inh(nModels);
    int LIF_Cla2 = addNeuronModel_LIF_Cla(nModels);
    int DA_STDP2 = addSynapseModel_DA_STDP(weightUpdateModels);

    model.setGPUDevice(ID_DEVICE); 
    model.setDT(DT);
    model.setPrecision(_FTYPE);
    model.setName("model");

    // policy_net
    model.addNeuronPopulation("PPoi1", NPoi, Poi1, p_Poi1, ini_Poi1);
    model.addNeuronPopulation("PExc1", NExc, LIF_Exc1, p_Exc1, ini_Exc1);
    model.addNeuronPopulation("PInh1", NInh, LIF_Inh1, p_Inh1, ini_Inh1);
    model.addNeuronPopulation("PCla1", NCla, LIF_Cla1, p_Cla1, ini_Cla1);
    // target_net
    model.addNeuronPopulation("PPoi2", NPoi, Poi2, p_Poi2, ini_Poi2);
    model.addNeuronPopulation("PExc2", NExc, LIF_Exc2, p_Exc2, ini_Exc2);
    model.addNeuronPopulation("PInh2", NInh, LIF_Inh2, p_Inh2, ini_Inh2);
    model.addNeuronPopulation("PCla2", NCla, LIF_Cla2, p_Cla2, ini_Cla2);

    // policy_net
    model.addSynapsePopulation("P2E1", DA_STDP1, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PPoi1", "PExc1", ini_DA_STDP_PE1, p_DA_STDP_PE1, postSynV1, postExpP2E1);
    model.addSynapsePopulation("E2C1", DA_STDP1, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc1", "PCla1", ini_DA_STDP_EC1, p_DA_STDP_EC1, postSynV1, postExpP2E1);

    model.addSynapsePopulation("E2I1", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc1", "PInh1", ini_NSYNAPSE_EI1, p_NSYNAPSE_EI1, postSynV1, postExpE2I1);
    model.addSynapsePopulation("I2E1", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PInh1", "PExc1", ini_NSYNAPSE_IE1, p_NSYNAPSE_IE1, postSynV1, postExpI2E1);

    // target_net
    model.addSynapsePopulation("P2E2", NSYNAPSE, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PPoi2", "PExc2", ini_DA_STDP_PE2, p_DA_STDP_PE2, postSynV2, postExpP2E2);
    model.addSynapsePopulation("E2C2", NSYNAPSE, DENSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc2", "PCla2", ini_DA_STDP_EC2, p_DA_STDP_EC2, postSynV2, postExpP2E2);

    model.addSynapsePopulation("E2I2", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PExc2", "PInh2", ini_NSYNAPSE_EI2, p_NSYNAPSE_EI2, postSynV2, postExpE2I2);
    model.addSynapsePopulation("I2E2", NSYNAPSE, SPARSE, INDIVIDUALG, NO_DELAY, EXPDECAY, "PInh2", "PExc2", ini_NSYNAPSE_IE2, p_NSYNAPSE_IE2, postSynV2, postExpI2E2);

    model.finalize();
    fprintf(stdout, "#model created.\n");
}
