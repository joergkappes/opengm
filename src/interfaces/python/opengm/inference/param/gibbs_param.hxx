#ifndef ICM_PARAM
#define ICM_PARAM

#include <string>
#include "param_exporter_base.hxx"
//solver specific
#include <opengm/inference/gibbs.hxx>

using namespace boost::python;

template<class DEPTH,class INFERENCE>
class InfParamExporterGibbs{

public:
   typedef typename INFERENCE::ValueType ValueType;
   typedef typename INFERENCE::IndexType IndexType;
   typedef typename INFERENCE::Parameter Parameter;
   typedef InfParamExporterGibbs<DEPTH,INFERENCE> SelfType;

   static void set
   (
      Parameter & p,
      const size_t steps,
      const bool useTemp,
      const typename INFERENCE::ValueType tempMin,
      const typename INFERENCE::ValueType tempMax,
      const ValueType periodeLength 
   ){
      p.useTemp_=useTemp,
      p.maxNumberOfSamplingSteps_=steps;
      p.numberOfBurnInSteps_=0;
      p.tempMin_=tempMin;
      p.tempMax_=tempMax;
      p.p_=periodeLength;
   }

   void static exportInfParam(const std::string & className,const std::vector<std::string> & subInfParamNames){
      class_<Parameter > (className.c_str(), init<>())
         .def_readwrite("steps", &Parameter::maxNumberOfSamplingSteps_,
         "Number of sampling steps"
         )
         .def_readwrite("useTemp", &Parameter::useTemp_,
         "use temperature"
         )
         .def_readwrite("tempMin", &Parameter::tempMin_,
         "Min Temperature in (0,1]"
         )
         .def_readwrite("tempMax", &Parameter::tempMax_,
         "Min Temperature in (0,1]"
         )
         .def_readwrite("periodeLength", &Parameter::p_,
         "periode length"
         )
         .def("set", &SelfType::set, 
         (
            arg("steps")=size_t(1e6),
            arg("useTemp")=true,
            arg("tempMin")= ValueType(0.001),
            arg("tempMax")= ValueType(1.0),
            arg("periodeLength")= ValueType(1e5)
         )
         ,
         "Set the parameters values.\n\n"
         "All values of the parameter have a default value.\n\n"
         "Args:\n\n"
         "  steps: Number of sampling steps (default=100)\n\n"
         "  useTemp: use temperature (default=True)\n\n"
         "  tempMin: Temperature in (0,1] (default=0.001)\n\n"
         "  tempMax: Temperature in (0,1] (default=1.0)\n\n"
         "  periodeLength: perdiode length (default=1e5)\n\n"
         "Returns:\n"
         "  None\n\n"
         )
      ;
   }
};

template<class DEPTH,class GM,class ACC>
class InfParamExporter<DEPTH,opengm::Gibbs<GM,ACC> >  : public  InfParamExporterGibbs<DEPTH,opengm::Gibbs< GM,ACC> > {

};

#endif