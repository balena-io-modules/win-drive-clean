{
  "targets": [
    {
      "target_name": "drive-clean",
      "include_dirs" : [
        "<!(node -e \"require('nan')\")",
        "."
      ],
      "msvs_settings": {
        "VCLinkerTool": {
          "SetChecksum": "true"
        },
        "VCCLCompilerTool": {
          "ExceptionHandling": 1,
          "AdditionalOptions": [
            "/EHsc"
          ]
        }
      },
      "conditions": [
        [ 'OS=="win"', {
          "sources": [
            "src/drive-clean.cpp"
          ],
          "libraries": [
            "-lKernel32.lib"
          ]
        }]
      ]
    }
  ]
}
