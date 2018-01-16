#include "LibNvCaffe.h"

#include <iostream>
#include <fstream>

// Params
const bool bHalf2 = false;		// If set, run in FP16 mode
const bool bInt8 = false;		// If set, run in INT8 mode (Do not use!!!)

// std::vector<std::string> gInputs;
// std::map<std::string, DimsCHW> gInputDimensions;



// Logger for GIE info/warning/errors
class Logger : public ILogger			
{
	void log(Severity severity, const char* msg) override
	{
		// suppress info-level messages
		if (severity != Severity::kINFO)
			std::cout << msg << std::endl;
	}
} gLogger;

void createMemory(const ICudaEngine& engine, void** buffer, const std::string& name)
{
	size_t bindingIndex = engine.getBindingIndex(name.c_str());
	DimsCHW dimensions = static_cast<DimsCHW&&>(engine.getBindingDimensions((int)bindingIndex));
	size_t eltCount = dimensions.c()*dimensions.h()*dimensions.w(), memSize = eltCount * sizeof(float);

    void* deviceMem;
    
	CUDA_CHECK(cudaMalloc(&deviceMem, memSize));
	if (deviceMem == nullptr)
	{
		std::cerr << "Out of memory" << std::endl;
		exit(1);
	}

    *buffer = deviceMem;	
}

ICudaEngine* createEngine(std::string deployFile, std::string modelFile, std::string output_blob_name)
{
    ICudaEngine *engine;
    
    // create the builder
    IBuilder* builder = createInferBuilder(gLogger);
    
    // parse the caffe model to populate the network, then set the outputs
    INetworkDefinition* network = builder->createNetwork();
    ICaffeParser* parser = createCaffeParser();
    printf("Loading network... (%s, %s)\n", deployFile.c_str(), modelFile.c_str());
    const IBlobNameToTensor* blobNameToTensor = parser->parse(deployFile.c_str(),
                                                                modelFile.c_str(),
                                                                *network,
                                                                bHalf2 ? nvinfer1::DataType::kHALF:nvinfer1::DataType::kFLOAT);

    if (!blobNameToTensor)
        return nullptr;

    // for (int i = 0, n = network->getNbInputs(); i < n; i++)
    // {
    //     DimsCHW dims = static_cast<DimsCHW&&>(network->getInput(i)->getDimensions());
    //     gInputs.push_back(network->getInput(i)->getName());
    //     gInputDimensions.insert(std::make_pair(network->getInput(i)->getName(), dims));
    //     std::cout << "Input \"" << network->getInput(i)->getName() << "\": " << dims.c() << "x" << dims.h() << "x" << dims.w() << std::endl;
    // }

    // specify which tensors are outputs
    if (blobNameToTensor->find(output_blob_name.c_str()) == nullptr)
    {
        std::cout << "could not find output blob " << output_blob_name << std::endl;
        return nullptr;
    }
    network->markOutput(*blobNameToTensor->find(output_blob_name.c_str()));

    // for (int i = 0, n = network->getNbOutputs(); i < n; i++)
    // {
    //     DimsCHW dims = static_cast<DimsCHW&&>(network->getOutput(i)->getDimensions());
    //     std::cout << "Output \"" << network->getOutput(i)->getName() << "\": " << dims.c() << "x" << dims.h() << "x" << dims.w() << std::endl;
    // }

    // Build the engine
    builder->setMaxBatchSize(1); //(gParams.batchSize);
    builder->setMaxWorkspaceSize(1<<20); //gParams.workspaceSize<<20);
    builder->setHalf2Mode(bHalf2);

    engine = builder->buildCudaEngine(*network);
    if (engine == nullptr)
        std::cout << "could not build engine" << std::endl;

    parser->destroy();
    network->destroy();
    builder->destroy();
    // shutdownProtobufLibrary();

    return engine;
}

ICudaEngine* createEngineFromGIE(std::string gieFile)
{
    ICudaEngine *engine;
    
    printf("Loading engine... (%s)\n", gieFile.c_str());

    char *gieModelStream{nullptr};
    size_t size{0};
    std::ifstream file(gieFile.c_str(), std::ios::binary);
    std::cout << gieFile << std::endl;
    if (file.good()) {
        file.seekg(0, file.end);
        size = file.tellg();
        file.seekg(0, file.beg);
        gieModelStream = new char[size];
        //assert(gieModelStream);
        file.read(gieModelStream, size);
        file.close();
    }

    IRuntime* infer = createInferRuntime(gLogger);
    engine = infer->deserializeCudaEngine(gieModelStream, size, nullptr);
    if (gieModelStream) delete [] gieModelStream;

    if (engine == nullptr)
    std::cout << "could not build engine" << std::endl;

    return engine;
}
